
# Gráfkezelő program

## Funkciók

- `Bal egérgomb`: pont kiválasztása
- `V`: gráf pont létrehozása
- `Delete`: kiválasztott gráf pont(ok) törlése
- `E`: gráf él létrehozása két kiválasztott pont közt
- `D`: gráf él törlése két kiválasztott pont közt
- `Alt + D`: egy kiválasztott gráf pont összes élének törlése
- `T`: gráf mélységi bejárása egy megadott gráf ponttól kezdve
- `B`: gráf szélességi bejárása egy megadott gráf ponttól kezdve
- `Control + S`: gráf mentése
- `Drag and drop`: gráf betöltése `.grf` kiterjesztésű fájlból
- `Görgő fel/le`: be/kizoomolás
- `Nyíl gombok`: munkafelület mozgatása
- `R`: zoomolás és elmozgatás visszaállítása alaphelyzetbe

## Leírás

A program gráfok kezelésére alkalmas. A program megnyitását követően egy üres munkalap látható. Ezen a munkalapon fognak megjelenni a pontok és az élek, amik különböző billentyűkombinációkkal létrehozhatóak és törölhetőek.

Az elkészített gráfot el lehet menteni, ilyenkor három fájl jön létre egy `saves` nevű mappában:
- `.vrx` kiterjesztésű fájl: ebben a fájlban tárolódnak el a gráf pontjai és azok tulajdonságai
- `.edg` kiterjesztésű fájl: ebben a fájlban tárolódnak el a gráf élei és azok tulajdonságai
- `.grf` kiterjesztésű fájl: ezt a fájlt kell a programmal megnyitni, ha egy elmentett gráfot betölteni szeretnénk.

Fontos, hogy a gráf betöltéséhez mind a három fájlra szükség van, de csak a `.grf` kiterjesztésű fájlt kell a munkaterületre behúzni egy mappából. Mind a három fájlt a mentés időpontjával nevez el a program, ez alapján lehet a mentéseket azonosítani.

## Build

Telepítsd a `make` programot, és futtasd a mappában a `make build` parancsot.
