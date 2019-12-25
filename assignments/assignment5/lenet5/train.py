import torch
import os
import sys
import copy
import time
import argparse
import torchvision
from torch import optim, nn
from tqdm import trange
from torch.optim import lr_scheduler
from torch.utils.data import DataLoader
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from lenet5.net import LeNet5

def GetDevice():
    device = torch.device('cuda:1') if torch.cuda.is_available() else torch.device('cpu')
    print('select device', device)
    return device

def TrainAndSaveModel(model, loss, optimizer, scheduler, device, num_epochs=30, dataloader=None):
    num_train = len(dataloader.dataset)
    since = time.time()
    best_model = copy.deepcopy(model)
    best_acc = 0
    iter_num = 0
    inputs_num = 0

    for epoch in trange(num_epochs):
        print('Epoch {}/{}'.format(epoch + 1, num_epochs))
        print('-' * 10)

        running_loss = 0.0
        running_corrects = 0
        model.train() # set model to training mode
        for batch_num, training_batch in enumerate(dataloader):
            inputs, labels = training_batch
            inputs = inputs.to(device)
            labels = labels.to(device)
            inputs_num += inputs.size(0)

            # zero the gradient
            optimizer.zero_grad()

            outputs = model(inputs)
            _, preds = torch.max(outputs, 1)

            loss_value = loss(outputs, labels)
            loss_value.backward()
            optimizer.step()

            iter_loss = loss_value.item() * inputs.size(0)
            running_loss += iter_loss
            if iter_num % 300 == 0:
                print("     Iter {}, avg loss is {}".format(iter_num, running_loss / inputs_num))
            running_corrects += torch.sum(preds == labels.data)
            iter_num += 1

        epoch_acc = running_corrects.double() / num_train
        print("Epoch accuracy {}".format(epoch_acc))
        print()
        scheduler.step()

        if epoch_acc > best_acc:
            best_acc = epoch_acc
            best_model = copy.deepcopy(model.state_dict())

    now = time.time()
    total_time = now - since

    print('Training time is %f minutes, %f seconds.' % (total_time // 60, total_time % 60))
    print('Best acc is %f' % best_acc)
    model.load_state_dict(best_model)
    return model

if __name__ == '__main__':
    args = argparse.ArgumentParser(description='Lenet5 for MNIST Torch implementation')
    args.add_argument('--lr', type=float, dest='lr', help='learning rate', default=0.01)
    args.add_argument('--momentum', type=float, dest='momentum', help='momentum value', default=0.9)
    args.add_argument('--epoch', type=int, dest='epoch', help='training total epoch', default=10)
    args.add_argument('--batchsize', type=int, dest='batchsize', help='batch size in every iter', default=32)
    args.add_argument('--checkpoint', type=str, dest='checkpoint', help='checkpoint path to save', default='checkpoint/lenet.pth')
    args.add_argument('--datapath', type=str, dest='datapath', help='MNIST dataset path', default='./data')
    args = args.parse_args()

    device = GetDevice()

    transformImg = torchvision.transforms.Compose([torchvision.transforms.ToTensor(),
                                                   torchvision.transforms.Normalize([0.5], [0.5])])
    trainSet = torchvision.datasets.MNIST(root=args.datapath, train=True, download=True, transform=transformImg)
    testSet = torchvision.datasets.MNIST(root=args.datapath, train=False, download=True, transform=transformImg)
    trainDataLoader = DataLoader(trainSet, batch_size=args.batchsize, shuffle=True, num_workers=4)
    testDataLoader = DataLoader(testSet, batch_size=args.batchsize, shuffle=True, num_workers=4)

    model = LeNet5().to(device)
    # prepare loss function, optimizer and scheduler
    loss = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=args.lr, momentum=args.momentum)
    scheduler = lr_scheduler.StepLR(optimizer, step_size=10, gamma=0.1)

    best_model = TrainAndSaveModel(model, loss, optimizer, scheduler, device, args.epoch, trainDataLoader)
    if not os.path.isdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'checkpoint')):
        os.makedirs(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'checkpoint'))
    torch.save(best_model.state_dict(), args.checkpoint)
    print('success saved model.')