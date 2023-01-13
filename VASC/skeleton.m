clear all;
figure;
a=imread('BW.tiff');
[n,m]=size(a);
sanwei=zeros(n,m);
c=zeros(n,m);
d=zeros(n,m);
e=zeros(n,m);
f=zeros(n,m);
g=zeros(n,m);
subplot(1,2,1);
imshow(a);
title('原图像');
a=double(a);
for y=1:255
for i=2:(n-1)
    for j=2:(m-1)
        b=0;
        for k=(i-1):(i+1)
            for l=(j-1):(j+1)
                b=b+a(k,l);%周围9个点像素和

                if b>(255*9-10)
                 d(i,j)=255;
             else
                 d(i,j)=0;
                end
            end
        end
    end
end
if d==0
   break;
else
    a=d;
    sanwei=d;
end
  for i=2:(n-1)   
    for j=2:(m-1)       
        b=0;        
        for k=(i-1):(i+1)           
            for l=(j-1):(j+1)               
                b=b+sanwei(k,l);              
                if b>(255*9-10)               
                    c(i,j)=255;  
                else c(i,j)=0;
                end            
            end       
        end  
    end
end
for i=2:(n-1)   
    for j=2:(m-1)       
        b=0;      
        for k=(i-1):(i+1)        
            for l=(j-1):(j+1)           
                b=b+c(k,l);            
                if b>0              
                    g(i,j)=255;       
                else              
                    g(i,j)=0;        
                end         
            end       
        end  
    end
end
f=sanwei-g;%求sanwei中为白色 g为黑色的点
e=e|f; %区0矩阵相异的点，相同为0，相异为1
end
e=(e)*255;%转化正0~255
subplot(1,2,2);
imshow(e);%输出
title('骨化');
