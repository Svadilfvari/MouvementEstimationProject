
V= readmatrix('file_lisse1.txt')
U= readmatrix('file_lisse2.txt')

I=imread('woman2.bmp')
[rows, columns, numberOfColorChannels] = size(I);

dimX = rows
dimY = columns

Y = [0:1:dimX-2];
X = [0:1:dimY-2];

quiver(X,Y,U,V)
hold on
colormap ('hsv')

size (X)
size(Y)

size(U)
size(V)