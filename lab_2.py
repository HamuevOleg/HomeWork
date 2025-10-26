import asyncio

class Lab2:
    async def number_1(self):
        print ("="*20 + "part 1.1" + "="*20)

        s = 'ProgramareaInteractiva'
        print(f" a: {s[:-1]}")
        print(f" b: {s[:1]} ")
        print(f" c: {s[0:1]}")
        print(f" d: {s[:]}  ")
        print(f" e: {s[-1:]}")
        print(f" f: {s[2:5]}")
        print(f" g: {s[-3:-1]}")
        print(f" h: {s[1:9:2]}")
        print(f" i: {s[::-1]}")

        print("=" * 20 + "part 1.2" + "=" * 20)

        L = ['a', 'b', 'c', 'd', 'e']
        
        print(f" a: {L[-1]}")
        print(f" b: {L[:2]}")
        print(f" c: {L[::]}")
        print(f" d: {L[1:3:2]}")
        print(f" e: {L[2:len(L)]}")
        print(f" f: {L[len(L) - 2]}")
        print(f" g: {L[1] + L[3]}")
        print(f" h: {L[2] + L[-2]}")
        print(f" i: {2 * L[2:4]}")
        print(f" j: {L[int(int('3' * 2) / 11)]}")

        L[0:1] = ['x','y']
        # or create new list -> smth like l_for_k = ['a', 'b', 'c', 'd', 'e'] -> and then change 0-2
        # and also for var k -> smth like l_for_l = ['a', 'b', 'c', 'd', 'e'] -> and then change 0-2
        print(f" k: {L}")
        L[0:2] = ['Python']
        print(f" l: {L}")

        print("=" * 20 + "part 1.3" + "=" * 20)

        b = [34, 45, 56, 38]
        b.insert(-1, 12)
        print(f" a: {b}")

        b = [34, 45, 56, 38]
        b.pop()
        print(f" b: {b}")

        b = [34, 45, 56, 38]
        b.remove(34)
        print(f" c: {b}")

        b = [34, 45, 56, 38]
        b.append("doi")
        print(f" d: {b}")

        print(f" e: {b.index('doi')}")

        b = [34, 45, 56, 38]
        print(f" f: {b.count(34)}")

        b.reverse()
        print(f" g: {b}")

        b.sort()
        print(f" h: {b}")

        del(b[0:2])
        print(f" i: {b}")

        b.extend([1])
        print(f" j: {b}")



async def main():
    example = Lab2()
    await example.number_1()

if __name__ == "__main__":
    asyncio.run(main())