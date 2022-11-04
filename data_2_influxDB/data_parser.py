row = []
contentSave = ["","","","","","",""]
content = contentSave
printMsg = ["Time: ", " Wtemp: ", " Ltemp: ", " PhotoR1: ", " PhotoR2: ", " HallSenFlow: ", " HallSenDepth: "]



with open("input.txt") as file:
    read = file.readlines()
    for index,wert in enumerate(read):
        row.append(wert)

row.pop(0) #delets first element form row

for x,wert in enumerate(row):
    for index,wert in enumerate(printMsg):
        row[x] = row[x].replace(printMsg[index], "")
        while not row[x].startswith(" "):
            content[index] += row[x][0] 
            row[x] = row[x][1:]
    row[x] = content
    content = ["","","","","","",""]
    #content = contentSave


print(row)

