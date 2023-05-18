import numpy as np

np.set_printoptions(suppress=True,   precision=10,  threshold=2000,  linewidth=150)

test = np.load("four_mfcc_np.npy")

test_array = test[55]
test_array = test_array.astype(np.float32)
print(test_array.shape)

print("{",end="")
for i in range(0,49):
    print(" ")
    for j in range(0,10):
        print(test_array[i][j],",",end="")
print("}",end="")