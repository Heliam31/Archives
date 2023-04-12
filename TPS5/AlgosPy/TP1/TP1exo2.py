from random import *
from matplotlib import pyplot as plt

#FONCTIONS--------------------------------------------------

def eltMajDet(T):   
    i = 0
    iLgt = 0
    while(iLgt<(len(T)/2)):
        iLgt = 0
        for j in range(len(T)-1):
            if T[i]==T[j]:
                iLgt += 1
        i+=1
    return T[i-1]

def eltMajProba(T):
    iLgt = 0
    maj=0
    while iLgt < (len(T)/2):
        iLgt=0
        maj = choice(T)
        for j in range(len(T)-1):
            if maj == T[j]:
                iLgt+=1
    return maj
        
def tabAlea (n, a, b, k):
    T=[]
    m = randint(a, b)
    for i in range (k):
        T.append(m)
    
    for i in range(n-k):
        v = randint(a, b)
        while v == m:
            v=randint(a, b)
        T.append(v)
    shuffle(T)
    return T
    
def tabDeb (n, a, b, k):
    T=[]
    m = randint(a, b)
    for i in range (k-1):
        T.append(m)
    
    for i in range(n-k):
        v = randint(a, b)
        while v == m:
            v=randint(a, b)
        T.append(v)
    shuffle(T)
    sol=[m]
    for i in range(n-1):
        sol.append(T[i])
    return sol
    
def tabFin (n, a, b, k):
    T=[]
    m = randint(a, b)
    for i in range(n-k):
        v = randint(a, b)
        while v == m:
            v=randint(a, b)
        T.append(v)
        
    for i in range (k):
        T.append(m)
    return(T)
#EXECUTION--------------------------------------------------
print(tabFin(10, 1, 100, 6))
