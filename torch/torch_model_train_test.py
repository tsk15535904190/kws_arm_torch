import torch
import numpy as np
import torch.nn.functional as F
from torchsummary import summary


one_mfcc = np.load("mfcc_data/one_mfcc_np.npy")
two_mfcc = np.load("mfcc_data/two_mfcc_np.npy")
three_mfcc = np.load("mfcc_data/three_mfcc_np.npy")
four_mfcc = np.load("mfcc_data/four_mfcc_np.npy")
five_mfcc = np.load("mfcc_data/five_mfcc_np.npy")
background_mfcc = np.load("mfcc_data/background_mfcc_np.npy")
print(background_mfcc.shape)
#Function to Convert to ONNX 
def convert_onnx(model): 

    # set the model to inference mode 
    model.eval() 

    # Let's create a dummy input tensor  
    dummy_input = torch.randn(1, 1, 49, 10, requires_grad=True)  

    # Export the model   
    torch.onnx.export(model,         # model being run 
         dummy_input,       # model input (or a tuple for multiple inputs) 
         "best_model.onnx",       # where to save the model  
         export_params=True,  # store the trained parameter weights inside the model file 
         opset_version=11,    # the ONNX version to export the model to 
         do_constant_folding=True,  # whether to execute constant folding for optimization 
         input_names = ['input'],   # the model's input names 
         output_names = ['output'], # the model's output names 
         dynamic_axes={'input' : {0 : 'batch_size'},    # variable length axes 
                                'output' : {0 : 'batch_size'}}) 
    print(" ") 
    print('Model has been converted to ONNX')

class Net(torch.nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.conv1 = torch.nn.Conv2d(in_channels=1, out_channels=64,
                                     kernel_size=(4, 10), padding=(1, 4), stride=(2, 2))
        self.fc1 = torch.nn.Linear(in_features=12*5*64, out_features=6)
        self.avgpool = torch.nn.AvgPool2d(
            kernel_size=(1*4), stride=(1, 1), padding=(0, 0))
        self.depthwise = torch.nn.Conv2d(in_channels=64, out_channels=64, kernel_size=(
            3, 3), padding=(1, 1), stride=(1, 1), groups=64)
        self.pointwise = torch.nn.Conv2d(
            in_channels=64, out_channels=64, kernel_size=1)
        self.pooling = torch.nn.MaxPool2d(kernel_size=(2, 1))

    def dw_conv(self, x):
        x = self.depthwise(x)
        x = F.relu(x)
        x = self.pointwise(x)
        x = F.relu(x)
        return x

    def forward(self, x):
        x = self.conv1(x)
        x = F.relu(x)
        x = self.dw_conv(x)
        x = self.dw_conv(x)
        x = self.dw_conv(x)
        x = self.dw_conv(x)
        #x = self.avgpool(x)
        x = self.pooling(x)
        x = x.view(int(x.size(0)), -1)
        x = self.fc1(x)
        return x


train_model = Net()


# 构建损失
criterion = torch.nn.CrossEntropyLoss()
# 构建优化器
# optimizer = torch.optim.SGD(model.parameters(),lr = 0.001,momentum=0.8) #0.4741 conv2
# optimizer = torch.optim.SGD(model.parameters(),lr = 0.001) #0.0037 conv2    0.4931 conv1
optimizer = torch.optim.RMSprop(train_model.parameters(),lr=0.001,alpha=0.9)#0.0000 conv2    0.0000 conv1
# optimizer = torch.optim.Adam(train_model.parameters(), lr=0.001, betas=(0.9, 0.99))  # 0.0000 conv2  0.0000 conv1


def train(model , epochs):
    epoches = epochs
    best_loss_val = 1
    targets = torch.tensor([0, 1, 2, 3, 4,5])
    for epoch in range(epoches):
        for i in range(0, 1700):
            inputs = torch.Tensor(([background_mfcc[i]],[one_mfcc[i]], [two_mfcc[i]], [
                                  three_mfcc[i]], [four_mfcc[i]], [five_mfcc[i]]))
            outputs = model(inputs)
            loss = criterion(outputs, targets)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            loss_val = loss.data.numpy()
        if loss_val<best_loss_val:
            torch.save(model, 'best_model.pth')
            best_loss_val = loss_val
            print("saved as \"best_model.pth\"")
            print("best_loss_val:",best_loss_val)
        print('Epoch: ', epoch, '| train loss: %.10f' % loss_val)
        
    





def test(model):
    nothing = 0
    one = 0
    two = 0
    three = 0
    four = 0
    five = 0
    for i in range(1700, 2000):
        inputs = torch.Tensor(([background_mfcc[i]],[one_mfcc[i]], [two_mfcc[i]], [
                                  three_mfcc[i]], [four_mfcc[i]], [five_mfcc[i]]))
        outputs = model(inputs)
        pred_y = torch.max(outputs, 1)[1].data.numpy().squeeze()
        if pred_y[0] != 0 :
            nothing +=1
        if pred_y[1] != 1 :
            one +=1
        if pred_y[2] != 2 :
            two +=1
        if pred_y[3] != 3 :
            three +=1
        if pred_y[4] != 4 :
            four +=1
        if pred_y[5] != 5 :
            five +=1
    print(nothing,one,two,three,four,five)
    print((1-nothing/300),(1-one/300),(1-two/300),(1-three/300),(1-four/300),(1-five/300))

# train(train_model,50)
test_model = torch.load('best_model.pth')
test(test_model)
#convert_onnx(test_model)

summary(test_model, input_size=[(1, 49, 10)],device="cpu")

