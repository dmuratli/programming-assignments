def import_inventory():
  productlist=open("products.txt", "r")
  productslinebyline=productlist.readlines()
  productlist.close()
  productdictionary={}
  for line in productslinebyline:
    line=line.strip().lower().split("-")
    for a in range(len(line)):
      line[a]=line[a].split("_")
      if line[a][0] not in productdictionary:
        productdictionary[line[a][0]]=int(line[a][1])
      else:
        productdictionary[line[a][0]]+=int(line[a][1])
  return productdictionary

def sell_product(productdictionary):
  tobesold=input("Please enter products to sell: ")
  tobesold=tobesold.strip().lower().split("-")
  for b in range(len(tobesold)):
    tobesold[b]=tobesold[b].split("_")
    if tobesold[b][0] in productdictionary:
      if int(tobesold[b][1])<productdictionary[tobesold[b][0]]:
        productdictionary[tobesold[b][0]]-=int(tobesold[b][1])
        print(tobesold[b][1], tobesold[b][0], "sold.")
      elif int(tobesold[b][1])==productdictionary[tobesold[b][0]]:
        productdictionary.pop(tobesold[b][0])
        print(tobesold[b][1], tobesold[b][0], "sold.")
      else:
        print("There is not enough", tobesold[b][0], "in inventory.")
    else:
      print(tobesold[b][0], "does not exist in inventory.")

def show_remaining(productdictionary):
  namelist=sorted(list(productdictionary.keys()))
  if len(namelist)!=0:
    for c in range(len(namelist)):
      print(namelist[c], ":", productdictionary[namelist[c]])
  else:
    print("Inventory is empty!")

#Deniz Muratli

# DO NOT MODIFY THIS CODE CELL, JUST RUN IT

products = import_inventory()
decision = ""
while decision != "3":
  print("*---------------------------")
  print("[1] Sell products")
  print("[2] Show remaining inventory")
  print("[3] Terminate")

  decision = input("Please enter your decision: ")
  print("____________________________")
  if decision == "1":
    sell_product(products)
  elif decision == "2":
    show_remaining(products)
  elif decision == "3":
    print("Terminating...")
  else:
    print("Invalid input!")
