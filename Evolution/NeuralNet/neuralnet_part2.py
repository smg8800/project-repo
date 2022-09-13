# neuralnet.py
# ---------------
# Licensing Information:  You are free to use or extend this projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to the University of Illinois at Urbana-Champaign
#
# Created by Justin Lizama (jlizama2@illinois.edu) on 10/29/2019
# Modified by Mahir Morshed for the spring 2021 semester
# Modified by Joao Marques (jmc12) for the fall 2021 semester 

"""
This is the main entry point for MP3. You should only modify code
within this file and neuralnet_part1.py,neuralnet_leaderboard -- the unrevised staff files will be used for all other
files and classes when code is run, so be careful to not modify anything else.
"""

import numpy as np

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from utils import get_dataset_from_arrays
from torch.utils.data import DataLoader

class NeuralNet(nn.Module):
    def __init__(self, lrate, loss_fn, in_size, out_size):
        """
        Initializes the layers of your neural network.

        @param lrate: learning rate for the model
        @param loss_fn: A loss function defined as follows:
            @param yhat - an (N,out_size) Tensor
            @param y - an (N,) Tensor
            @return l(x,y) an () Tensor that is the mean loss
        @param in_size: input dimension
        @param out_size: output dimension
        """
        super(NeuralNet, self).__init__()
        self.loss_fn = loss_fn
        self.lrate = lrate
        #self.net = torch.nn.Sequential(torch.nn.Linear(in_size, 150),torch.nn.ReLU(), torch.nn.Dropout(0.25),torch.nn.Linear(150,out_size))
        self.net = torch.nn.Sequential(torch.nn.Conv2d(3,6,kernel_size=3), torch.nn.ReLU(), torch.nn.MaxPool2d(2,2), torch.nn.Conv2d(6,16,3), torch.nn.ReLU(), torch.nn.MaxPool2d(2,2), torch.nn.Flatten(), torch.nn.Linear(576,120), torch.nn.ReLU(), torch.nn.Linear(120,84), torch.nn.Linear(84,out_size))
        self.optimizer = optim.SGD(self.net.parameters(),self.lrate, momentum=0.9)
        
    def forward(self, x):
        """Performs a forward pass through your neural net (evaluates f(x)).

        @param x: an (N, in_size) Tensor
        @return y: an (N, out_size) Tensor of output from the network
        """
        return self.net(x.view(x.shape[0],3,32,32))

    def step(self, x,y):
        """
        Performs one gradient step through a batch of data x with labels y.

        @param x: an (N, in_size) Tensor
        @param y: an (N,) Tensor
        @return L: total empirical risk (mean of losses) for this batch as a float (scalar)
        """
        inp = self.forward(x)
        loss = self.loss_fn(inp,y)
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()
        return loss.detach().cpu().numpy()

def fit(train_set,train_labels,dev_set,epochs,batch_size=100):
    """ Make NeuralNet object 'net' and use net.step() to train a neural net
    and net(x) to evaluate the neural net.

    @param train_set: an (N, in_size) Tensor
    @param train_labels: an (N,) Tensor
    @param dev_set: an (M,) Tensor
    @param epochs: an int, the number of epochs of training
    @param batch_size: size of each batch to train on. (default 100)

    This method _must_ work for arbitrary M and N.

    The model's performance could be sensitive to the choice of learning rate.
    We recommend trying different values in case your first choice does not seem to work well.

    @return losses: list of total loss at the beginning and after each epoch.
            Ensure that len(losses) == epochs.
    @return yhats: an (M,) NumPy array of binary labels for dev_set
    @return net: a NeuralNet object
    """
    lrate = 0.02
    net = NeuralNet(lrate, torch.nn.CrossEntropyLoss(),3072,4)
    losses = []
    train = (train_set - torch.mean(train_set))/torch.std(train_set)
    data = get_dataset_from_arrays(train,train_labels)
    training_generator = torch.utils.data.DataLoader(data, batch_size=batch_size)
    for i in range(epochs):
        loss_ = 0
        n = 0
        for idx, batch in enumerate(training_generator):
            loss_ += net.step(batch['features'],batch['labels'])
            n +=1
        losses.append(loss_/n)

    yhats = np.zeros(len(dev_set))
    new_set = (dev_set-torch.mean(train_set))/torch.std(train_set)
    new_set = new_set.view(dev_set.shape[0],3,32,32)
    set = net(new_set).detach().numpy()
    #set.view(dev_set[0],3,30,30)
    for i in range(len(dev_set)):
        yhats[i] = np.argmax(set[i])
    return losses, yhats.astype(int), net
