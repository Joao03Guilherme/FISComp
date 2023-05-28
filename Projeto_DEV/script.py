image = []
with open("f.txt", "r") as file:
    line = []
    for i in file:
        line.append(i.strip())
    image.append(line)

with open("fout.txt", "w") as file:
    for line in image:
        for val in line:
            file.write(f"{val},")