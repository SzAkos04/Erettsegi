SELECT
	fuvar.mikor,
    SUM(IF(tarifa.tipus = "Alkalmi", 1, gepkocsi.utasszam)) AS "utasok"
FROM
	fuvar
INNER JOIN
	tarifa ON fuvar.tarifaid = tarifa.id
INNER JOIN
	gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
WHERE
	gepkocsi.sofor = "Tari Norbert"
GROUP BY
	fuvar.mikor;