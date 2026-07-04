SELECT
	Concat(COUNT(*), " fuvar és ", SUM(fuvar.tav), " km távolság") AS "3 napi összegzés"
FROM
	fuvar;