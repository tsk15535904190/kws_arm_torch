import numpy as np
import math

M_PI = 3.14159265358979323846
M_2PI = 6.283185307179586476925286766559005

SAMP_LEN_MS = 1000
SAMP_FREQ = 16000
FRAME_LEN_MS = 40
FRAME_SHIFT_MS = 20
NUM_FBANK_BINS = 40  # How many Mel filters of the whole filter bank, each filter is so called a "bin"
MEL_LOW_FREQ = 20    # Lowest Mel frequency to consider
MEL_HIGH_FREQ = 4000 # Highest Mel frequency to consider
NUM_MFCC_COEFFS = 10 # All Mel filters are compressed to Mel features with DCT, how many Mel features to use

class MFCC():
    def __init__(self, num_mfcc_features:int, frame_len:int, num_fbank_bins=40,
            samp_freq:int=16000, mel_low_freq:float = 20, mel_high_freq:float=4000):
        self.num_mfcc_features = num_mfcc_features
        self.frame_len = frame_len
        self.NUM_FBANK_BINS = num_fbank_bins
        self.SAMP_FREQ = samp_freq
        self.MEL_LOW_FREQ = mel_low_freq
        self.MEL_HIGH_FREQ = mel_high_freq

        self.frame_len_padded = 2 ** math.ceil(math.log(frame_len) / math.log(2))
        self.frame = np.zeros(self.frame_len_padded, dtype = "double")
        self.buffer = np.zeros(self.frame_len_padded, dtype = "double")
        self.mel_energies = np.zeros(num_fbank_bins, dtype = "double")
        # create window function
        self.window_func = np.zeros(frame_len, dtype="double")
        for i in range(frame_len):
            self.window_func[i] = 0.5 - 0.5 * math.cos(M_2PI * i / frame_len)
        # create mel filterbank
        self.fbank_filter_first = np.zeros(self.NUM_FBANK_BINS, dtype="int32")
        self.fbank_filter_last = np.zeros(self.NUM_FBANK_BINS, dtype="int32")
        self.mel_fbank = self.create_mel_fbank()

        self.dct_matrix = self.create_dct_matrix(self.NUM_FBANK_BINS, num_mfcc_features)

    def MelScale(freq = 400.0):
        ret = 1127.0 * math.log(1.0 + freq / 700.0);
        return ret

    def InverseMelScale(mel_freq:float):
        ret = 700.0 * (math.exp(mel_freq / 1127.0) - 1.0)
        return ret

    def create_mel_fbank(self):
        num_fft_bins = self.frame_len_padded // 2;
        fft_bin_width = self.SAMP_FREQ / self.frame_len_padded
        mel_low_freq = MFCC.MelScale(self.MEL_LOW_FREQ)
        mel_high_freq = MFCC.MelScale(self.MEL_HIGH_FREQ)
        mel_freq_delta = (mel_high_freq - mel_low_freq) / (self.NUM_FBANK_BINS + 1);

        this_bin = np.zeros(num_fft_bins, dtype="double")
        mel_fbank = [None] * self.NUM_FBANK_BINS
        for bin in range (self.NUM_FBANK_BINS):
            left_mel = mel_low_freq + bin * mel_freq_delta;
            center_mel = mel_low_freq + (bin + 1) * mel_freq_delta;
            right_mel = mel_low_freq + (bin + 2) * mel_freq_delta;

            first_index = -1
            last_index = -1;
            for i in range(num_fft_bins):
                freq = (fft_bin_width * i);  # center freq of this fft bin.
                mel = MFCC.MelScale(freq);
                this_bin[i] = 0.0
                if mel > left_mel and mel < right_mel:
                    if mel <= center_mel:
                        weight = (mel - left_mel) / (center_mel - left_mel)
                    else:
                        weight = (right_mel-mel) / (right_mel-center_mel)                   
                    this_bin[i] = weight
                    if first_index == -1:
                        first_index = i
                    last_index = i
                elif mel >= right_mel:
                    break               
            self.fbank_filter_first[bin] = first_index;
            self.fbank_filter_last[bin] = last_index;
            curMelBankWidth = last_index-first_index+1
            mel_fbank[bin] = np.zeros(curMelBankWidth, dtype="double")
            mel_fbank[bin][:] = this_bin[first_index:last_index+1]
        return mel_fbank

    def create_dct_matrix(self, in_count:int, out_count:int):
        M = np.zeros(in_count * out_count, dtype="double")
        normalizer = (2.0 / in_count) ** 0.5
        for k in range(out_count):
            for n in range(in_count):
                M[k * in_count + n] = normalizer * math.cos(M_PI / in_count * (n + 0.5) * k)
        return M;
        

    def mfcc_compute(self, audio_data, mfcc_out):
        # Compute num_mfcc_features (10) for a single frame (40ms)
        # 40ms audio (640 samples) -> Hanming window -> FFT -> spectrum -> Mel filterbank -> take log -> Compress by DCT
        # 1. TensorFlow way of normalizing .wav data to (-1, 1)
        self.frame[:self.frame_len] = audio_data / 32768.0
        self.frame[self.frame_len:] = 0
        # 2. apply window function
        self.frame[:self.frame_len] *= self.window_func
        # 3. Compute FFT
        rfftAry = np.fft.rfft(self.frame)
        # 4. Convert to power spectrum square root
        # frame is stored as complex128, size is len(self.frame)//2+1, first is DC offset
        self.buffer[1:len(rfftAry)-1] = (np.absolute(rfftAry))[1:-1]
        self.buffer[0] = np.absolute(rfftAry[0].real)
        self.buffer[len(rfftAry)-1] = np.absolute(rfftAry[0].imag)

        # 5. Apply mel filterbanks
        for bin in range(self.NUM_FBANK_BINS):
            j = 0
            mel_energy = 0
            first_index = self.fbank_filter_first[bin]
            last_index = self.fbank_filter_last[bin]
            for i in range(first_index, last_index + 1):
                mel_energy += self.buffer[i] * self.mel_fbank[bin][j]
                j += 1
            if mel_energy == 0:
                mel_energy = 1.0E-10 # 1.175494351e-38
            self.mel_energies[bin] = mel_energy

        # 6. Take log
        for bin in range(self.NUM_FBANK_BINS):
            self.mel_energies[bin] = math.log(self.mel_energies[bin])

        # 7. Take DCT to compress Mel-Spectrum to Mel features. NUM_FBANK_BINS (40) compressed to num_mfcc_features (10)
        for i in range(self.num_mfcc_features):
            sum = 0
            for j in range(self.NUM_FBANK_BINS):
                sum += self.dct_matrix[i * self.NUM_FBANK_BINS + j] * self.mel_energies[j]
            mfcc_out[i] = sum
        return 0


class KWS_MFCC():
    def __init__(self, audio_data_buffer, samp_len_ms=SAMP_LEN_MS, samp_freq=SAMP_FREQ, frame_len_ms=FRAME_LEN_MS,
            frame_shift_ms=FRAME_SHIFT_MS, num_mfcc_coefs=NUM_MFCC_COEFFS,
            num_fbank_bins=NUM_FBANK_BINS, mel_low_freq=MEL_LOW_FREQ, mel_high_freq=MEL_HIGH_FREQ):
        self.SAMP_LEN_MS = samp_len_ms
        self.SAMP_FREQ = samp_freq
        self.SAMP_LEN_PTS = samp_len_ms * samp_freq // 1000
        self.FRAME_LEN_MS = frame_len_ms
        self.FRAME_SHIFT_MS = frame_shift_ms
        self.NUM_MFCC_COEFFS = num_mfcc_coefs
        self.NUM_FBANK_BINS = num_fbank_bins
        self.MEL_LOW_FREQ = mel_low_freq
        self.MEL_HIGH_FREQ = mel_high_freq

        self.SAMP_KHZ = self.SAMP_FREQ // 1000
        self.MFCC_DEC_BITS = 1
        self.FRAME_SHIFT = int(self.SAMP_KHZ * self.FRAME_SHIFT_MS)
        self.NUM_FRAMES = 1 + (self.SAMP_LEN_MS - self.FRAME_LEN_MS) // self.FRAME_SHIFT_MS
        self.MFCC_BUFFER_SIZE = (self.NUM_FRAMES * self.NUM_MFCC_COEFFS)
        self.FRAME_LEN = int(self.SAMP_KHZ * self.FRAME_LEN_MS)

        self.audio_buffer = np.zeros(self.SAMP_LEN_PTS, dtype="int16")
        if audio_data_buffer is not None:
            if len(audio_data_buffer) >= self.SAMP_LEN_PTS:
                self.audio_buffer = audio_data_buffer[:self.SAMP_LEN_PTS].copy()
            else:
                self.audio_buffer[-len(audio_data_buffer):] = audio_data_buffer.copy()
        self.init_mfcc()

    def init_mfcc(self):
        self.mfcc_buffer_size = 0
        self.mfcc_buffer_head = 0

        self.mfcc = MFCC(self.NUM_MFCC_COEFFS, self.FRAME_LEN, samp_freq=self.SAMP_FREQ,
            num_fbank_bins=self.NUM_FBANK_BINS, mel_low_freq=self.MEL_LOW_FREQ, mel_high_freq=self.MEL_HIGH_FREQ)
        self.mfcc_buffer = np.zeros(self.NUM_FRAMES * self.NUM_MFCC_COEFFS, dtype="double")
        self.audio_block_size = self.NUM_FRAMES * self.FRAME_SHIFT

    def extract_uint8_features(self, min=-247, max=30):
        u8RetAry = np.zeros(self.MFCC_BUFFER_SIZE, dtype="uint8")
        retAry = np.zeros(self.MFCC_BUFFER_SIZE, dtype="double")
        for i in range(self.MFCC_BUFFER_SIZE):
            retAry[i] = 255.0 * (self.mfcc_buffer[(i + self.mfcc_buffer_head) % \
                self.MFCC_BUFFER_SIZE] - min) / (max - min)
        out_data = np.asarray(np.round(retAry), dtype="uint8")
        out_data = out_data.reshape((self.NUM_FRAMES, self.NUM_MFCC_COEFFS))
        return out_data

    def extract_features(self, i16AudBuf=None):
        if i16AudBuf is not None:
            if len(i16AudBuf) >= self.SAMP_LEN_PTS:
                self.audio_buffer = i16AudBuf[-self.SAMP_LEN_PTS:].copy()
            else:
                newLen = len(i16AudBuf)
                self.audio_buffer[:self.SAMP_LEN_PTS-newLen] = self.audio_buffer[newLen:].copy()
                self.audio_buffer[-newLen:] = i16AudBuf.copy()

        for fraNdx in range(self.NUM_FRAMES):
            ofs = fraNdx * self.FRAME_SHIFT
            self.mfcc.mfcc_compute(self.audio_buffer[ofs:ofs + self.FRAME_LEN].copy(), 
                self.mfcc_buffer[self.mfcc_buffer_head:])
            self.mfcc_buffer_head = (self.mfcc_buffer_head + self.NUM_MFCC_COEFFS) % len(self.mfcc_buffer)
        return self.mfcc_buffer.copy()