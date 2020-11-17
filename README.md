# solving-differential-equations
Solving differential equations using the modified euler method modelled using C++

The example is for an infectious disease model called the SIS model. The model has two states S and I, and the equations are:

 dS/dt = αI − βSI,

 dI/dt = βSI − αI
 
This model has an equilibrium given by:

S = α/β, 

I = N − S

Check that this is what the numerical solution (i.e. the modified Euler method) approaches for large enough values of T , and with n large enough. Note that N here is a parameter of the model (like α and β).
