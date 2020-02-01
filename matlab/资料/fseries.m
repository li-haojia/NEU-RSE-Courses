function [A,B,F]=fseries(f,x,p,a,b)
% if nargin==3, a=-pi;b=pi; end
L=(b-a)/2; if a+b, f=subs(f,x,x+L+a);end
A = int(f,x,-L,L)/L; B=[]; F=A/2;
for n = 1:p
    an = int(f*cos(n*pi*x/L),x,-L,L)/L;A=[A,an];
    bn=int(f*sin(n*pi*x/L),x,-L,L)/L;
    B=[B,bn];
    F=F+an*cos(n*pi*x/L)+bn*sin(n*pi*x/L);
end
% if a+b,F=subs(F,x,x-L-a);end