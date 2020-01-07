import torch.nn as nn
import torch.nn.functional as F

class LeNet5(nn.Module):
    def __init__(self):
        super(LeNet5, self).__init__()
        # input is 32 * 32, first layer is conv layer, so we need padding equals 2 to fill the data
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=6, kernel_size=5, stride=1, padding=2, bias=True)
        self.max_pool_1 = nn.MaxPool2d(kernel_size=2)
        self.conv2 = nn.Conv2d(in_channels=6, out_channels=16, kernel_size=5, stride=1, bias=True)
        self.max_pool_2 = nn.MaxPool2d(kernel_size=2)
        self.fc1 = nn.Linear(in_features=16 * 5 * 5, out_features=120)
        self.fc2 = nn.Linear(in_features=120, out_features=84)
        self.fc3 = nn.Linear(in_features=84, out_features=10)

    def forward(self, input):
        output = F.relu(self.conv1(input))
        output = self.max_pool_1(output)
        output = F.relu(self.conv2(output))
        output = self.max_pool_2(output)

        output = output.view(-1, 16 * 5 * 5)
        output = F.relu(self.fc1(output))
        output = F.relu(self.fc2(output))
        output = self.fc3(output)

        return output
