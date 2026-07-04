SELECT
	Concat(SUM(IF(fuvar.tav < 6, 1, 0)) / COUNT(*) * 100, "%") AS "arany"
FROM
	fuvar
INNER JOIN
	gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
WHERE
	gepkocsi.sofor = "Szokai Ada";