SELECT
	gepkocsi.sofor,
    gepkocsi.rendszam,
    gepkocsi.engedely
FROM
	gepkocsi
WHERE
	gepkocsi.vizsga = 1
GROUP BY
	gepkocsi.sofor
ORDER BY
	gepkocsi.sofor ASC;