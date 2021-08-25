# HRL_force_magnetomyography


- First the arduino sketch pulls data
- data is prepared for the neural net by the matlab file, which produces a .csv for each movement
- armband_LSTM is a neural net that parses .csv files, then trains and tests the neural net
- Generic LSTM classifier is included as proof of concept with a different data set

data is included in this repo so neural net can be run, but the data is bad. Put armband_LSTM.ipynb into the same directory as the data to run.
