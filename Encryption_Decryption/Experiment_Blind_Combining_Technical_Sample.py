import math

code=int(input("Please enter the code recorded at the begining of the experiment 1: "))
code2=int(input("Please enter the code recorded at the begining of the experiment 2: "))
n=code
n1=code2
def primeFactors(n):
    fact=[]
    while n % 2 == 0:
        fact.append(2)
        n = n / 2
    for i in range(3,int(math.sqrt(n))+1,2):
            while n % i== 0:
                fact.append(i)
                n = n / i
    if n > 2:
        fact.append(n)
    return(fact)
   
a=[11, 13, 17, 19, "Row A"]
b=[23, 29, 31, 37, "Row B"]
c=[41, 43, 47, 53,"Row C"]
d=[59, 61, 67, 71,"Row D"]

randomiser=[103, 107, 109, 113, 127, 131, 137, 139, 149, 151]

factored=primeFactors(code)
factored2=primeFactors(code2)
factored.sort()
factored2.sort()

output=''
output2=''

for i in range(len(factored)):
    if factored[i] in a:
        output+="Mix " +a[4]+" from first entered experiment, with "
        if factored2[i] in a:
            output+=a[4]+" from second entered experiment."
        if factored2[i] in b:
            output+=b[4]+" from second entered experiment."
    if factored[i] in b:
        output+="Mix " +b[4]+" from first entered experiment, with "
        if factored2[i] in a:
            output+=a[4]+" from second entered experiment."
        if factored2[i] in b:
            output+=b[4]+" from second entered experiment."
    
    if factored[i] in c:
        output2+="Mix " +c[4]+" from first entered experiment, with "
        if factored2[i] in c:
            output2+=c[4]+" from second entered experiment."
        if factored2[i] in d:
            output2+=d[4]+" from second entered experiment."
    if factored[i] in d:
        output2+="Mix " +d[4]+" from first entered experiment, with "
        if factored2[i] in c:
            output2+=c[4]+" from second entered experiment."
        if factored2[i] in d:
            output2+=d[4]+" from second entered experiment."
            


           
print(output)
print(output2)
        
