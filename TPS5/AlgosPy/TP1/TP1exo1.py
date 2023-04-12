from random import *
from matplotlib import pyplot as plt # chargement d ' un des modules de matplotlib


#FONCTIONS--------------------------------------------------

def entiersAleatoires(n,a, b):
    sol=[]
    for i in range(n):
        sol.append(randint(a,b))
    return sol

def entiersAleatoires2(n,a, b):
    sol=[]
    for i in range(n):
        sol.append(randrange(a,b))
    return sol
    
def flottantsAleatoires(n):
    sol=[]
    for i in range(n):
        sol.append(random())
    return sol
    
def flottantsAleatoires2(n, a, b):
    sol=[]
    for i in range(n):
        sol.append(uniform(a, b))
    return sol

def pointsDisque(n):
    sol=[]
    for i in range(n):
        nb=[]
        test=True
        while(test):
            nb = flottantsAleatoires2(2, -1, 1)
            if (nb[0]**2) + (nb[1]**2) <= 1:
                test=False
        sol.append(nb)
    return sol

def pointsDisque2(n):
    sol=[]
    for i in range(n):
        nb=[]
        test=True
        nb = flottantsAleatoires2(2, -1, 1)
        while(test):
            if (nb[0]**2) + (nb[1]**2) <= 1:
                test=False
            else:
                nb[1] = flottantsAleatoires2(1, -1, 1)[0]
        sol.append(nb)
    return sol        

def affichagePoints(L):
    X = [x for x,y in L]    
    Y = [y for x,y in L]    
    plt.scatter(X, Y, s = 1)  
    plt.axis('square') 
    plt.show()

def aleatoireModulo(N):
    sol = getrandbits(N.bit_length())
    return sol%N

def aleatoireRejet(N):
    sol=getrandbits(N.bit_length())
    while sol>N:
        sol=getrandbits(N.bit_length())
    return sol
    

            
#EXECUTION--------------------------------------------------

    #exo 1
'''
L1=entiersAleatoires(1000, 0, 100)

plt.subplot(2, 1, 1)
plt.hist(L1, bins=100)
plt.show()

L2=entiersAleatoires2(1000, 0, 100)

plt.hist(L2, bins=100)
plt.show()
'''
    #exo 2
'''
L3=flottantsAleatoires(1000)
L4=flottantsAleatoires2(1000, -3, 10)

plt.subplot(2, 1, 2)
plt.plot(L3)
plt.show()

plt.plot(L4)
plt.show()
'''
    #exo 3
'''
L5=pointsDisque(100000)
L6=pointsDisque2(100000)

plt.subplot(2,1,1)
affichagePoints(L5)
plt.subplot(2,1,2)
affichagePoints(L6)
'''
    #exo 4
'''
Lmod=[]
for i in range(10000):
    Lmod.append(aleatoireModulo(100))

Lrej=[]
for i in range(10000):
    Lrej.append(aleatoireRejet(100))

plt.figure()

plt.subplot(2, 1, 1)
plt.hist(Lmod, bins=100)
plt.show
plt.subplot(2, 1, 2)
plt.hist(Lrej, bins=100)
plt.show()
'''

