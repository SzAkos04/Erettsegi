SELECT DISTINCT
	gepkocsi.sofor
FROM
	gepkocsi
INNER JOIN
	fuvar on gepkocsi.rendszam = fuvar.rendszam
GROUP BY
	gepkocsi.sofor,
    fuvar.mikor
HAVING
	SUM(fuvar.tav) >= 80;