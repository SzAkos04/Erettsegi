SELECT DISTINCT
	gepkocsi.sofor
FROM
	gepkocsi
INNER JOIN
	fuvar ON gepkocsi.rendszam = fuvar.rendszam
WHERE
	DATE(fuvar.mikor) = "2025-10-12" AND
    fuvar.tav BETWEEN 10 AND 15 AND
    (gepkocsi.rendszam LIKE "%3%" OR gepkocsi.rendszam LIKE "%5%")
ORDER BY
	gepkocsi.sofor ASC;