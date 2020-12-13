for max_step=[1000 10000 50000  100000  500000];
    x=zeros(1,max_step);
    y=zeros(1,max_step);
    for n=1:max_step
        r=rand();
        if r<=0.01
            x(n+1)=0;
            y(n+1)=0.16*y(n);
        elseif r<=0.08
            x(n+1)=0.2*x(n)-0.26*y(n);
            y(n+1)=0.23*x(n)+0.22*y(n)+1.6;
        elseif r<=0.15
            x(n+1)=-0.15*x(n)+0.28*y(n);
            y(n+1)=0.26*x(n)+0.24*y(n)+0.44;
        else
            x(n+1)=0.85*x(n)+0.04*y(n);
            y(n+1)=-0.04*x(n)+ 0.85*y(n)+1.6;
        end
    end
    plot(x,y,'.','Color', 'g', 'MarkerSize',1)
    title(['N = ' num2str(max_step)])
    drawnow
    pause(0.5)
end