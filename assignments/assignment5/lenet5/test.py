import torch
import os
import sys
import argparse
import torchvision
from torch.utils.data import DataLoader
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from lenet5.net import LeNet5

def evaluate(model_path):
    num_test = len(testDataLoader.dataset)
    # load the weights and reproduce the model here
    model = LeNet5()
    print("Loading model from: {}".format(model_path))
    model.load_state_dict(torch.load(model_path, map_location='cpu'))
    model.eval()

    running_corrects = 0
    for batch_num, testing_batch in enumerate(testDataLoader):
        inputs, labels = testing_batch

        with torch.set_grad_enabled(False):
            outputs = model(inputs)
            _, preds = torch.max(outputs, 1)

        running_corrects += torch.sum(preds == labels.data)

    print('Testing accuracy is {}'.format(running_corrects.double() / num_test))

if __name__ == '__main__':
    args = argparse.ArgumentParser(description='Lenet5 for MNIST Torch implementation, for mnist testing')
    args.add_argument('--checkpoint', type=str, dest='checkpoint', help='checkpoint path to save', default='checkpoint/lenet.pth')
    args.add_argument('--datapath', type=str, dest='datapath', help='MNIST dataset path', default='./data')
    args.add_argument('--batchsize', type=int, dest='batchsize', help='batch size in every iter', default=32)
    args = args.parse_args()

    transformImg = torchvision.transforms.Compose([torchvision.transforms.ToTensor(),
                                                   torchvision.transforms.Normalize([0.5], [0.5])])
    testSet = torchvision.datasets.MNIST(root=args.datapath, train=False, download=True, transform=transformImg)
    testDataLoader = DataLoader(testSet, batch_size=args.batchsize, shuffle=True, num_workers=4)
    evaluate(args.checkpoint)