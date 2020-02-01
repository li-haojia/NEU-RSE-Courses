syms x;
f=abs(x)/x;
xx=[-pi:pi/200:pi];
xx=xx(xx~=0);
xx = sort([xx,-eps,eps]);
yy = subs(f,x,xx)
plot(xx,yy), hold on, 
for n=1:20, 
    [a,b,f1]=fseries(f,x,n,-pi,pi);y1=subs(f1,x,xx);plot(xx,y1);
end