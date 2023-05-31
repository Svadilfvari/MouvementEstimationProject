
V= readmatrix('file1_echan.txt')
U= readmatrix('file2_echan.txt')

%ïmages laugh 1 et laugh2
I=imread('woman1.bmp')
[rows, columns, numberOfColorChannels] = size(I);

dimX = rows
dimY = columns


Y = [0:1:dimX-2];
X = [0:1:dimY-2];

figure(1)
quiver(X,Y,U,V)
hold on
colormap ('hsv')

size (X)
size(Y)

size(U)
size(V)