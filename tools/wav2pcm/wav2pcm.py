from __future__ import print_function
from pathlib import Path

import sys
import os
import struct
import wave
from builtins import range


def main(arg):
    if(len(arg) < 2):
        print('Usage: %s file.wav' % (arg[0]))
        return

    wav_file_path = arg[1]
    path_str = Path(wav_file_path)
    wav_file_name = path_str.stem
    #
    wave_read = wave.open(wav_file_path, 'r')
    wav_channels = wave_read.getnchannels()
    wav_samplewidth = wave_read.getsampwidth()
    wav_samplerate = wave_read.getframerate()
    wav_frames = wave_read.getnframes()

    print('------------------------------------')
    print('%-16s | %s' % ('file_name', wav_file_name))
    print('%-16s | %10d' % ('wav_channels', wav_channels))
    print('%-16s | %10d' % ('wav_samplewidth', wav_samplewidth))
    print('%-16s | %10d' % ('wav_samplerate', wav_samplerate))
    print('%-16s | %10d' % ('wav_frames', wav_frames))
    print('------------------------------------')

    header_file_name = 'audio_'+wav_file_name
    print(header_file_name)
    header_file = open(str(path_str.parent) + '/' + header_file_name + '.h', 'w+')
    header_file.seek(0)

    # protect
    print(header_file_name.upper())
    header_file.write('#ifndef __' + header_file_name.upper() + '_H__\n')
    header_file.write('#define __' + header_file_name.upper() + '_H__\n')

    header_file.write('#include <stdint.h>\n')

    header_file.write('\n// ------------------------------------')
    header_file.write('\n// %-16s | %16d' % ('wav_channels', wav_channels))
    header_file.write('\n// %-16s | %16d' %
                      ('wav_samplewidth', wav_samplewidth))
    header_file.write('\n// %-16s | %16d' % ('wav_samplerate', wav_samplerate))
    header_file.write('\n// %-16s | %16d' % ('wav_frames', wav_frames))
    header_file.write('\n// ------------------------------------')
    header_file.write('\n')

    header_file.write('uint32_t %s_rate = %d;\n' %
                      (header_file_name, wav_samplerate))
    header_file.write('uint32_t %s_frames = %d;\n' %
                      (header_file_name, wav_frames))
    header_file.write('const int16_t %s[] = {\n' % header_file_name)

    for i in range(wav_frames):
        val, = struct.unpack('h', wave_read.readframes(1))
        # data = str(val+32768)
        data = str(val)
        header_file.write(data)
        if(i != (wav_frames-1)):
            header_file.write(',')
        else:
            header_file.write('\n};\n')

    header_file.write('\n')
    header_file.write('#endif //__' + header_file_name.upper() + '_H__\n')
    header_file.close()


if __name__ == "__main__":
    main(sys.argv)
