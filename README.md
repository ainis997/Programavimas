# Programa

## Funkcionalumas

### Programa:

- nuskaito arba sugeneruoja studentų duomenis (vardą, pavardę, pažymius, egzamino įvertinimą);
- apskaičiuoja galutinį balą (pagal vidurkį arba medianą);
- pateikia visus reikalingus duomenis lentelėje.

## Programos trukmės testavimai

### 1. Programos versija su std::vector

##### 1 000 įrašų

##### 10 000 įrašų

##### 100 000 įrašų

##### 1 000 000 įrašų

##### 10 000 000 įrašų

![alt text](image-27.png)

### 2. Programos versija su std::deque

##### 10 000 000 įrašų:

![alt text](image-28.png)

### 3. Programos versija su std::list

##### 1 000 įrašų:

##### 10 000 įrašų:

##### 100 000 įrašų:

##### 1 000 000 įrašų:

##### 10 000 000 įrašų:

### 1. Failo sukūrimas

Kuriant studentų duomenų failus, kiekvienam studentui parinkta sugeneruoti 15 pažymių. Testavimas vykdytas 5 skirtingais generuosimų studentų (įrašų) skaičiais. Matuotas failo kūrimo ir jo uždarymo laikas. Testavimas atliktas po 5 kartus kiekvienam skirtingam failo dydžiui (nuo 1 tūkst. iki 10 mln. įrašų).

##### 1 000 įrašų:

![alt text](./images/image.png)
![alt text](./images/image-5.png)
![alt text](./images/image-6.png)
![alt text](./images/image-7.png)
![alt text](./images/image-8.png)

##### 10 000 įrašų:

![alt text](./images/image-1.png)
![alt text](./images/image-9.png)
![alt text](./images/image-10.png)
![alt text](./images/image-11.png)
![alt text](./images/image-12.png)

##### 100 000 įrašų:

![alt text](./images/image-2.png)
![alt text](./images/image-13.png)
![alt text](./images/image-14.png)
![alt text](./images/image-15.png)
![alt text](./images/image-16.png)

##### 1 000 000 įrašų:

![alt text](./images/image-3.png)
![alt text](./images/image-17.png)
![alt text](./images/image-18.png)
![alt text](./images/image-19.png)
![alt text](./images/image-20.png)

##### 10 000 000 įrašų:

![alt text](./images/image-4.png)
![alt text](./images/image-21.png)
![alt text](./images/image-22.png)
![alt text](./images/image-23.png)
![alt text](./images/image-24.png)

##### Vidurkiai

| Failo įrašų sk.    | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.   | 10 mln. |
| ------------------ | ---------- | ---------- | ---------- | -------- | ------- |
| Laikų vidurkis (s) | 0,00290086 | 0,02646834 | 0,2644242  | 2,502434 | 26,7269 |

### 2. Duomenų apdorojimas

Kiekvienam testavimo kartojimui buvo parenkamas atitinkamo įrašų skaičiaus įvesties failas ir buvo parenkami tie patys studentų rikiavimo parametrai (pagal vidurkį didėjimo tvarka). Testavimas atliktas po 5 kartus kiekvienam skirtingam failo dydžiui (nuo 1 tūkst. iki 10 mln. įrašų).

##### 1 000 įrašų:

![alt text](./images/image-25.png)
![alt text](./images/image-26.png)
![alt text](./images/image-27.png)
![alt text](./images/image-28.png)
![alt text](./images/image-29.png)

##### 10 000 įrašų:

![alt text](./images/image-30.png)
![alt text](./images/image-31.png)
![alt text](./images/image-32.png)
![alt text](./images/image-33.png)
![alt text](./images/image-34.png)

##### 100 000 įrašų:

![alt text](./images/image-35.png)
![alt text](./images/image-36.png)
![alt text](./images/image-37.png)
![alt text](./images/image-38.png)
![alt text](./images/image-39.png)

##### 1 000 000 įrašų:

![alt text](./images/image-40.png)
![alt text](./images/image-41.png)
![alt text](./images/image-42.png)
![alt text](./images/image-43.png)
![alt text](./images/image-44.png)

##### 10 000 000 įrašų:

![alt text](./images/image-45.png)
![alt text](./images/image-46.png)
![alt text](./images/image-47.png)
![alt text](./images/image-48.png)
![alt text](./images/image-49.png)

##### Vidurkiai

| Failo įrašų sk.              | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.    | 10 mln.  |
| ---------------------------- | ---------- | ---------- | ---------- | --------- | -------- |
| Nuskaitymas (s)              | 0,0082389  | 0,05655488 | 0,5449784  | 5,452364  | 54,92564 |
| Surikiavimas (s)             | 0,0008362  | 0,00967478 | 0,10048548 | 1,281598  | 15,90642 |
| Išskirstymas (s)             | 0,00039198 | 0,00354602 | 0,03276502 | 0,3771846 | 3,883046 |
| Gerų studentų išvedimas (s)  | 0,00092336 | 0,00672996 | 0,06695008 | 0,6438512 | 6,414396 |
| Blogų studentų išvedimas (s) | 0,00074054 | 0,00489324 | 0,04797708 | 0,4505216 | 4,5188   |
| Visa programa\* (s)          | 0,01113098 | 0,08139888 | 0,7931562  | 8,205518  | 85,6483  |

<sup>\*Visa programa — visos programos trukmė (neįskaitant vartotojo įvesties intarpų).</sup>
