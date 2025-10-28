balance = int(input("Enter Total Balance: "))
cake_order_cost = int(input("Enter Cake's Order Cost: "))
cake_cost_per_kilogeram = int(input("Enter Cake's Cost per kilogeram: "))
candles_cost = int(input("Enter Candles' Cost: "))
hat_cost = int(input("Enter Birthday Hat's Cost: "))
balloons_cost = int(input("Enter Balloons' Cost: "))
reservation_cost = int(input("Enter Reservation's Cost: "))
gift_1_cost = int(input("Enter Gift Number 1's Cost: "))
solution = []
def fitness(solution):
    return (100 - abs(30 - (solution[0] + 2*solution[1] - 3*solution[2] + solution[3] + 4*solution[4]+ solution[5])))
print (fitness)