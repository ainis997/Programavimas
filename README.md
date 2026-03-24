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

![alt text](images/image-203.png)
![alt text](images/image-202.png)
![alt text](images/image-201.png)
![alt text](images/image-200.png)
![alt text](images/image-204.png)

##### 10 000 įrašų:

![alt text](images/image-205.png)
![alt text](images/image-206.png)
![alt text](images/image-207.png)
![alt text](images/image-208.png)
![alt text](images/image-209.png)

##### 100 000 įrašų:

![alt text](images/image-210.png)
![alt text](images/image-211.png)
![alt text](images/image-212.png)
![alt text](images/image-213.png)
![alt text](images/image-214.png)

##### 1 000 000 / 10 000 000 įrašų:

Išmatuoti programos trukmės su 1 mln. ir 10 mln. įrašų kiekiais nepavyko: programa nesibaigė netgi palaukus pusvalandį. Atsižvelgiant į studentų skirstymo algoritmo kvadratinį sudėtingumą (ištrinant elementą, turi būti perstumdyti likę elementai), duomenų kiekiui padidėjus 10 kartų, laikas teoriškai turėtų pailgėti apie 100 k., taigi, lyginant su 100 tūkst. įrašų konteinerio testavimu, kuris truko apie 40 s, 1 mln. įrašų konteinerio testavimas galėtų trukti bent 40x100 = 4000 s (virš valandos), o 10 mln. — 4000x100 = 400 000 s (virš 4.5 paros). Tačiau, atsižvelgiant į didesnį nei 100 k. skirtumą tarp 100 tūkst. ir 10 tūkst. įrašų konteinerių testavimų (39,6094 / 0,326577 ≈ 121 k.), reali 1 mln. ir 10 mln. įrašų konteinerių testavimų trukmė galėtų būti dar didesnė.

### std::deque

##### 1 000 įrašų:

![alt text](images/image-248.png)
![alt text](images/image-247.png)
![alt text](images/image-246.png)
![alt text](images/image-245.png)
![alt text](images/image-249.png)

##### 10 000 įrašų:

![alt text](images/image-244.png)
![alt text](images/image-243.png)
![alt text](images/image-242.png)
![alt text](images/image-241.png)
![alt text](images/image-240.png)

##### 100 000 įrašų:

![alt text](images/image-239.png)
![alt text](images/image-238.png)
![alt text](images/image-237.png)
![alt text](images/image-236.png)
![alt text](images/image-235.png)

##### 1 000 000 įrašų:

![alt text](images/image-230.png)
![alt text](images/image-231.png)
![alt text](images/image-232.png)
![alt text](images/image-233.png)
![alt text](images/image-234.png)

##### 10 000 000 įrašų:

![alt text](images/image-226.png)
![alt text](images/image-215.png)
![alt text](images/image-227.png)
![alt text](images/image-228.png)
![alt text](images/image-229.png)

### std::list:

##### 1 000 įrašų:

![alt text](images/image-264.png)
![alt text](images/image-263.png)
![alt text](images/image-262.png)
![alt text](images/image-261.png)
![alt text](images/image-260.png)

##### 10 000 įrašų:

![alt text](images/image-259.png)
![alt text](images/image-258.png)
![alt text](images/image-257.png)
![alt text](images/image-256.png)
![alt text](images/image-255.png)

##### 100 000 įrašų:

![alt text](images/image-254.png)
![alt text](images/image-253.png)
![alt text](images/image-252.png)
![alt text](images/image-251.png)
![alt text](images/image-250.png)

##### 1 000 000 įrašų:

![alt text](images/image-216.png)
![alt text](images/image-217.png)
![alt text](images/image-218.png)
![alt text](images/image-219.png)
![alt text](images/image-220.png)

##### 10 000 000 įrašų:

![alt text](images/image-221.png)
![alt text](images/image-222.png)
![alt text](images/image-223.png)
![alt text](images/image-224.png)
![alt text](images/image-225.png)

### Laikų vidurkiai

##### std::vector:

| Failo įrašų sk.   | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln. | 10 mln. |
| ----------------- | ---------- | ---------- | ---------- | ------ | ------- |
| Nuskaitymas (s)   | 0,00320758 | 0,03402558 | 0,333312   | -      | -       |
| Surikiavimas (s)  | 0,00012632 | 0,0015466  | 0,01933338 | -      | -       |
| Išskirstymas (s)  | 0,00243372 | 0,2740764  | 39,09528   | -      | -       |
| Visa programa (s) | 0,00854098 | 0,326577   | 39,6094    | -\*    | -\*     |

<sup>\*Pagal 100 tūkst. matavimo duomenis, teorinė 1 mln. testavimo trukmė: virš 1 val., 10 mln. — virš 4,5 paros.</sup>

##### std::deque:

| Failo įrašų sk.   | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.     | 10 mln.   |
| ----------------- | ---------- | ---------- | ---------- | ---------- | --------- |
| Nuskaitymas (s)   | 0,00353708 | 0,0383836  | 0,3346878  | 3,314098   | 33,33642  |
| Surikiavimas (s)  | 0,00047344 | 0,006487   | 0,09090332 | 1,257108   | 15,91488  |
| Išskirstymas (s)  | 0,00006486 | 0,00074886 | 0,00790908 | 0,08166356 | 0,7776834 |
| Visa programa (s) | 0,00909804 | 0,0626871  | 0,5943708  | 6,372664   | 77,88376  |

##### std::list:

| Failo įrašų sk.   | 1 tūkst.   | 10 tūkst.  | 100 tūkst. | 1 mln.    | 10 mln.  |
| ----------------- | ---------- | ---------- | ---------- | --------- | -------- |
| Nuskaitymas (s)   | 0,00570298 | 0,05225144 | 0,4573822  | 4,584298  | 45,38584 |
| Surikiavimas (s)  | 0,00010288 | 0,00130258 | 0,0304274  | 0,588567  | 10,31716 |
| Išskirstymas (s)  | 0,00004944 | 0,00076784 | 0,01517834 | 0,1673388 | 2,165952 |
| Visa programa (s) | 0,01036566 | 0,07639782 | 0,7316634  | 8,249734  | 136,6016 |

##### Išvados:

Išvados: lyginant su 1-osios strategijos programos versija, std::deque ir std::list visos programos trukmė išliko panaši, nors studentų išskirstymo trukmė gana ryškiai sumažėjo. Tuo tarpu std::vector programa itin ženkliai sulėtėjo. Matyti, jog std::vector programos trukmė auga eksponentiškai, priklausomai nuo duomenų (įrašų) kiekio. Dėl to nepavyko nustatyti tikslios std::vector programos trukmės apdorojant 1 mln. ir 10 mln. įrašų. Atsižvelgiant į mažesnio studentų sk. išskirstymo laikus ir į išskirstymo algoritmo teorinį sudėtingumą, tikėtina, jog std::vector programoje 1 mln. studentų išskirstymas matuotinas valandomis, o 10 mln. — paromis.
