#---------------------FONCTIONS--------------------
#1
def clause (s):
    str=s.split()
    sol=[]
    for i in range(len(str)): 
        if (int(str[i])!=0):
            sol.append(int(str[i]))
    return sol

def parseur(nom):
    var=0
    form=[]
    with open(nom) as f:
        for ligne in f:
            str=ligne.split()
            if str[0] == "p" :
                var=str[2]
            elif str[0]!="c":
                str = clause(ligne.replace("p",""))
                form.append(str)
                var=int(var)
    return (form, var)

#2
def est_valide(F, A):
    f=[]
    sol=1
    for i in F:
        cl=[]
        val=-1
        for j in i:
            if j<0:
                cl.append(-A[abs(j)-1])
            else:
                cl.append(A[abs(j)-1])
        for j in cl:
            if j==1:
                val=1
        f.append(val)
    for i in f:
        if i==-1:
            sol=-1
    return sol
    


#---------------------TESTS-------------------------
print("clause: ",clause("1 2 -3 0 \n"))
print("parseur: ",parseur('cnf/simple_v3_c2.cnf'))
print("est_valide true: ",est_valide([[1, -3], [2, 3, -1]],[1,1,1]))
print("est_valide false: ",est_valide([[1, -3], [2, 3, -1]],[0,0,0]))