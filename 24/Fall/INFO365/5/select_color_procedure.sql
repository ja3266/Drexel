create or replace PROCEDURE PCG_SELECT (P_Gameboard_ID integer, P_Color_Name varchar2) AS
BEGIN
  PCG_SELECT_COLOR(P_Gameboard_ID, USER, P_Color_Name);
  COMMIT;
END;