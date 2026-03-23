# Programa

## Funkcionalumas

### Programa:

- nuskaito arba sugeneruoja studentų duomenis (vardą, pavardę, pažymius, egzamino įvertinimą);
- apskaičiuoja galutinį balą (pagal vidurkį arba medianą);
- pateikia visus reikalingus duomenis lentelėje.

## Programos trukmės testavimai

Programos ir kai kurių jos etapų trukmė išmatuota trims programos versijoms, naudojančioms skirtingus duomenų konteinerius: std::vector, std::deque ir std::list. Testavimai atlikti kiekvienai versijai su 5 skirtingų dydžių failų apdorojimu (nuo 1 tūkst. iki 10 mln. įrašų), su 5 pakartojimais kiekvienu atveju.

Testavimo sistemos parametrai:

- CPU: AMD Ryzen 5 4600H 3GHz
- RAM: 16 GB
- SSD: Lexar SSD NM710 1TB

### 1. Programos versija su std::vector

##### 1 000 įrašų

![alt text](images/image-75.png)
![alt text](images/image-74.png)
![alt text](images/image-73.png)
![alt text](images/image-72.png)
![alt text](images/image-71.png)

##### 10 000 įrašų

![alt text](images/image-70.png)
![alt text](images/image-69.png)
![alt text](images/image-68.png)
![alt text](images/image-67.png)
![alt text](images/image-66.png)

##### 100 000 įrašų

![alt text](images/image-65.png)
![alt text](images/image-64.png)
![alt text](images/image-63.png)
![alt text](images/image-62.png)
![alt text](images/image-61.png)

##### 1 000 000 įrašų

![alt text](images/image-60.png)
![alt text](images/image-59.png)
![alt text](images/image-58.png)
![alt text](images/image-57.png)
![alt text](images/image-27.png)

##### 10 000 000 įrašų

![alt text](images/image-52.png)
![alt text](images/image-53.png)
![alt text](images/image-54.png)
![alt text](images/image-55.png)
![alt text](images/image-56.png)

### 2. Programos versija su std::deque

##### 1 000 įrašų:

![alt text](images/image-51.png)
![alt text](images/image-50.png)
![alt text](images/image-49.png)
![alt text](images/image-48.png)
![alt text](images/image-47.png)

##### 10 000 įrašų:

![alt text](images/image-46.png)
![alt text](images/image-45.png)
![alt text](images/image-44.png)
![alt text](images/image-43.png)
![alt text](images/image-42.png)

##### 100 000 įrašų:

![alt text](images/image-41.png)
![alt text](images/image-40.png)
![alt text](images/image-39.png)
![alt text](images/image-38.png)
![alt text](images/image-37.png)

##### 1 000 000 įrašų:

![alt text](images/image-32.png)
![alt text](images/image-33.png)
![alt text](images/image-34.png)
![alt text](images/image-35.png)
![alt text](images/image-36.png)

##### 10 000 000 įrašų:

![alt text](images/image-28.png)
![alt text](images/image-26.png)
![alt text](images/image-29.png)
![alt text](images/image-30.png)
![alt text](images/image-31.png)

### 3. Programos versija su std::list

##### 1 000 įrašų:

![alt text](images/image-25.png)
![alt text](images/image-24.png)
![alt text](images/image-23.png)
![alt text](images/image-22.png)
![alt text](images/image-21.png)

##### 10 000 įrašų:

![alt text](images/image-20.png)
![alt text](images/image-19.png)
![alt text](images/image-18.png)
![alt text](images/image-17.png)
![alt text](images/image-16.png)

##### 100 000 įrašų:

![alt text](images/image-15.png)
![alt text](images/image-14.png)
![alt text](images/image-13.png)
![alt text](images/image-12.png)
![alt text](images/image-11.png)

##### 1 000 000 įrašų:

![alt text](images/image-6.png)
![alt text](images/image-7.png)
![alt text](images/image-8.png)
![alt text](images/image-9.png)
![alt text](images/image-10.png)

##### 10 000 000 įrašų:

![alt text](images/image-1.png)
![alt text](images/image-2.png)
![alt text](images/image-3.png)
![alt text](images/image-4.png)
![alt text](images/image-5.png)

### Laikų vidurkiai

##### std::vector:

| Failo įrašų sk.   | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.    | 10 mln.  |
| ----------------- | ---------- | ---------- | ---------- | --------- | -------- |
| Nuskaitymas (s)   | 0,0034203  | 0,0309502  | 0,3051384  | 3,036604  | 30,2957  |
| Surikiavimas (s)  | 0,00013062 | 0,00148628 | 0,01846376 | 0,2391284 | 2,929308 |
| Išskirstymas (s)  | 0,00009908 | 0,00081048 | 0,00806456 | 0,0992962 | 2,559528 |
| Visa programa (s) | 0,00648488 | 0,0460721  | 0,4485966  | 4,58635   | 48,77302 |

##### std::deque:

| Failo įrašų sk.   | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.    | 10 mln.  |
| ----------------- | ---------- | ---------- | ---------- | --------- | -------- |
| Nuskaitymas (s)   | 0,0095191  | 0,032712   | 0,3172748  | 3,129548  | 31,40262 |
| Surikiavimas (s)  | 0,00049726 | 0,00698256 | 0,09231658 | 1,281324  | 15,66556 |
| Išskirstymas (s)  | 0,00014776 | 0,0015741  | 0,01706468 | 0,1747522 | 1,78443  |
| Visa programa (s) | 0,0070822  | 0,05854308 | 0,5698436  | 6,184886  | 74,05166 |

##### std::list:

| Failo įrašų sk.   | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.    | 10 mln.  |
| ----------------- | ---------- | ---------- | ---------- | --------- | -------- |
| Nuskaitymas (s)   | 0,00717774 | 0,04976302 | 0,44904    | 4,491188  | 45,95596 |
| Surikiavimas (s)  | 0,00007962 | 0,0012681  | 0,02743122 | 0,5778892 | 10,14206 |
| Išskirstymas (s)  | 0,0000953  | 0,00165964 | 0,01984636 | 0,2471198 | 3,514694 |
| Visa programa (s) | 0,01023278 | 0,0727979  | 0,712057   | 8,099776  | 138,1736 |

Išvada: programos versija su std::vector veikia greičiausiai, su std::deque — apie 1,5 k. lėčiau, o su std::list lėčiausiai — kone 3 k. lėčiau nei su std::vector ir kone 2 k. lėčiau nei su std::deque.

## 2. strategija

### std::vector

##### 1 000 įrašų:

![alt text](images/image-99.png)
![alt text](images/image-98.png)
![alt text](images/image-97.png)
![alt text](images/image-96.png)
![alt text](images/image-95.png)

##### 10 000 įrašų:

![alt text](images/image-94.png)
![alt text](images/image-93.png)
![alt text](images/image-92.png)
![alt text](images/image-91.png)
![alt text](images/image-90.png)

##### 100 000 įrašų:

![alt text](images/image-89.png)
![alt text](images/image-88.png)
![alt text](images/image-87.png)
![alt text](images/image-86.png)
![alt text](images/image-85.png)

##### 1 000 000 įrašų:

![alt text](images/image-83.png)
![alt text](images/image-82.png)
![alt text](images/image-81.png)
![alt text](images/image-80.png)
![alt text](images/image-84.png)

##### 10 000 000 įrašų:

![alt text](images/image.png)
![alt text](images/image-76.png)
![alt text](images/image-77.png)
![alt text](images/image-78.png)
![alt text](images/image-79.png)

### std::deque

##### 1 000 įrašų:

![alt text](images/image-124.png)
![alt text](images/image-123.png)
![alt text](images/image-122.png)
![alt text](images/image-121.png)
![alt text](images/image-120.png)

##### 10 000 įrašų:

![alt text](images/image-119.png)
![alt text](images/image-118.png)
![alt text](images/image-117.png)
![alt text](images/image-116.png)
![alt text](images/image-115.png)

##### 100 000 įrašų:

![alt text](images/image-114.png)
![alt text](images/image-113.png)
![alt text](images/image-112.png)
![alt text](images/image-111.png)
![alt text](images/image-110.png)

##### 1 000 000 įrašų:

![alt text](images/image-109.png)
![alt text](images/image-108.png)
![alt text](images/image-107.png)
![alt text](images/image-106.png)
![alt text](images/image-102.png)

##### 10 000 000 įrašų:

![alt text](images/image-103.png)
![alt text](images/image-104.png)
![alt text](images/image-105.png)
![alt text](images/image-100.png)
![alt text](images/image-101.png)

### Laikų vidurkiai

##### std::vector:

| Failo įrašų sk.   | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.     | 10 mln.   |
| ----------------- | ---------- | ---------- | ---------- | ---------- | --------- |
| Nuskaitymas (s)   | 0,0040183  | 0,03123856 | 0,3007366  | 3,017114   | 30,29264  |
| Surikiavimas (s)  | 0,0001338  | 0,00148878 | 0,01830784 | 0,237852   | 2,897784  |
| Išskirstymas (s)  | 0,00000148 | 0,0000097  | 0,00009196 | 0,03723346 | 0,3877502 |
| Visa programa (s) | 0,00662542 | 0,04521112 | 0,437131   | 4,486016   | 46,64658  |

##### std::deque:

| Failo įrašų sk.   | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.    | 10 mln.    |
| ----------------- | ---------- | ---------- | ---------- | --------- | ---------- |
| Nuskaitymas (s)   | 0,00372502 | 0,0364244  | 0,3261494  | 3,22165   | 32,15156   |
| Surikiavimas (s)  | 0,00054708 | 0,00646088 | 0,09260052 | 1,256646  | 15,64806   |
| Išskirstymas (s)  | 0,00000264 | 0,00001978 | 0,00018554 | 0,0060925 | 0,06289772 |
| Visa programa (s) | 0,00784538 | 0,05936244 | 0,579933   | 6,23446   | 74,53918   |

##### std::list:
