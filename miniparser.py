a = []
for line in open("IDENTIFIER","r"):
    a.append(line)
for line in sorted(a,key=len):
    print("strncmp(word,\""+line.rstrip()+"\",length)==0||")
 
