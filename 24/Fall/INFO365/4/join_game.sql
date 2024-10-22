create or replace PROCEDURE PCG_JOIN (P_Gameboard_ID integer) AS
BEGIN
  PCG_JOIN_GAMEBOARD(P_Gameboard_ID, USER);
  COMMIT;
END;
