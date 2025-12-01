import my_math
import pandas as pd

class tasks:
    def __init__(self):
        pass
    
    def task2(self):
        print("="*20 + " Task 2 " + "="*20)

        number_of_tasks = 15
        
        # 1 FOR loop + 5 IF conditions inside
        for i in range(0, number_of_tasks):
            if i == 0:
                print(str(i) + " because of condition")
            elif i == 1:
                print(str(i) + " because of condition")
            elif i == 2:
                print(str(i) + " because of condition")
            elif i == 3:
                print(str(i) + " because of condition")
            elif i == 6:
                print(str(i) + " because of condition")

        # 4 more FOR loops to reach total of 5
        for j in range(1):
            print("Extra for loop executed")
        
        for k in [1]:
            print("Another for loop executed")
            
        for l in "A":
            print("String for loop executed")
            
        for m in range(0, 1):
            print("Final for loop executed")

        # 5 WHILE loops to reach total of 5
        w1 = 0
        while w1 < 1:
            print("While loop 1 done")
            w1 += 1

        w2 = 0
        while w2 < 1:
            print("While loop 2 done")
            w2 += 1

        w3 = True
        while w3:
            print("While loop 3 done")
            w3 = False

        w4 = 10
        while w4 > 9:
            print("While loop 4 done")
            w4 -= 1

        w5 = 0
        while w5 != 1:
            print("While loop 5 done")
            w5 = 1
    
    def task3(self):
        print("="*20 + " Task 3 " + "="*20)
        
        val1 = 10
        val2 = 3

        res1 = my_math.super_add(val1, val2)
        print("1. Addition result: " + str(res1))

        res2 = my_math.super_sub(val1, val2)
        print("2. Subtraction result: " + str(res2))

        res3 = my_math.super_mult(val1, val2)
        print("3. Multiplication result: " + str(res3))

        res4 = my_math.super_div(val1, val2)
        print("4. Division result: " + str(res4))

        res5 = my_math.super_pow(val1, val2)
        print("5. Power result: " + str(res5))

        res6 = my_math.super_mod(val1, val2)
        print("6. Modulo result: " + str(res6))

    def task4(self):
        print("\n" + "="*20 + " Task 4 " + "="*20)
        
        excel_data = [] # List to store data for Excel export

        # Program 1: Create List and double values
        nums = [1, 2, 3, 4, 5]
        doubled = [x * 2 for x in nums]
        print("1. List doubling: " + str(doubled))
        excel_data.append({"Program": "1", "Input": str(nums), "Output": str(doubled)})

        # Program 2: Create Dictionary and access value
        user = {"id": 101, "login": "admin"}
        login = user["login"]
        print("2. Dict access: " + login)
        excel_data.append({"Program": "2", "Input": str(user), "Output": login})

        # Program 3: List of Dictionaries (Filtering)
        people = [
            {"name": "Dan", "age": 20},
            {"name": "Ion", "age": 15},
            {"name": "Ana", "age": 25}
        ]
        adults = [p["name"] for p in people if p["age"] >= 18]
        print("3. Filter adults: " + str(adults))
        excel_data.append({"Program": "3", "Input": str(people), "Output": str(adults)})

        # Program 4: Dictionary keys to List
        grades = {"Math": 9, "CS": 10, "Sport": 10}
        subjects = list(grades.keys())
        print("4. Subjects list: " + str(subjects))
        excel_data.append({"Program": "4", "Input": str(grades), "Output": str(subjects)})

        # Program 5: Merging lists into Dictionary
        keys = ["a", "b", "c"]
        vals = [1, 2, 3]
        merged = dict(zip(keys, vals))
        print("5. Merge to dict: " + str(merged))
        excel_data.append({"Program": "5", "Input": f"{keys}, {vals}", "Output": str(merged)})

        # Saving to Excel
        try:
            df = pd.DataFrame(excel_data)
            df.to_excel("results.xlsx", index=False)
            print(">>> Data saved to results.xlsx successfully")
        except Exception as e:
            print("Error saving Excel: " + str(e))


def main():
    t = tasks()

    print("MENU")
    task = input("Select task to run (2, 3, or 4): ")

    if task == "2":
        t.task2()
    elif task == "3":
        t.task3()
    elif task == "4":
        t.task4()

if __name__ == "__main__":
    main()