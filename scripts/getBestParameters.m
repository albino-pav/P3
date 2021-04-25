% File must be opened with MATLAB, and executed with the program inside the
% directory \\wsl$\Ubuntu-20.04\home\user\PAV\P3\scripts

rth = 0;
pth = 0;
dth = 0;
cth = 0; 
result = 0;

maxrth = 0;
maxpth = 0;
maxdth = 0;
maxcth = 0; 
maxResult = 0;

data = fopen('../results.txt', 'r');
while (~feof(data))
    parameters = fscanf(data, '%f %f %f\n');
    rth = parameters(1);
    pth = parameters(2);
    dth = parameters(3);
    cth = parameters(4); 
    results = fscanf(data, '===>	TOTAL:	%f%31c'); %===> TOTAL: %f%c\n\n');
    result = results(1);
    if (result > maxResult)
        maxResult = result;
        maxrth = rth;
        maxpth = pth;
        maxdth = dth;
        maxcth = cth; 
    end
end

fclose(data);

optimumlist = fopen('../testresults.txt', 'a+');
fprintf(optimumlist, 'rth = %0.2f\t pth = %0.2f\t dth = %0.3f\t cth = %0.4f\t====>\t %0.2f %%', maxrth, maxpth, maxdth, maxcth, maxResult);
fprintf(optimumlist, '\n');
fclose(optimumlist);

