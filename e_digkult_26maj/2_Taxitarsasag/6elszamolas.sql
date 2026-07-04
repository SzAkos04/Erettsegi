SELECT
    gepkocsi.sofor,
    gepkocsi.rendszam,
    SUM(tarifa.dij) AS bevetel
FROM
    fuvar
INNER JOIN
    tarifa ON fuvar.tarifaid = tarifa.id
INNER JOIN
    gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
GROUP BY
    gepkocsi.sofor
ORDER BY
    gepkocsi.sofor ASC;