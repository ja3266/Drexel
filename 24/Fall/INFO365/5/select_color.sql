create or replace PROCEDURE PCG_SELECT_COLOR (
    P_Gameboard_ID NUMBER,
    P_Player_ID VARCHAR2, 
    P_Color_Name VARCHAR2
)
IS
    c INTEGER;
    v_upper_player_id VARCHAR2(50); 
    v_upper_color_name VARCHAR2(50);
BEGIN
    -- Convert P_Player_ID to uppercase and store in the local variable
    v_upper_player_id := UPPER(P_Player_ID);
    v_upper_color_name := UPPER(P_Color_Name);

    IF NOT P_Gameboard_ID BETWEEN 100000 AND 999999 THEN
        RAISE_APPLICATION_ERROR(-20001,'Gameboard ID MUST be a 6-digit number');
    END IF;

        -- Validation: Is the Gameboard ID valid?
    SELECT COUNT(*) INTO c FROM PCG_GAMEBOARD g WHERE g.GAMEBOARD_ID = P_Gameboard_ID;
    IF c = 0 THEN
        RAISE_APPLICATION_ERROR(-20002, 'Gameboard ID (' || P_Gameboard_ID || ') is not valid.');
    END IF;

    -- Validation: Is the Player ID valid?
    SELECT COUNT(*) INTO c FROM PCG_PLAYER p WHERE p.PLAYER_ID = v_upper_player_id;
    IF c = 0 THEN
        RAISE_APPLICATION_ERROR(-20003, 'Player ID (' || v_upper_player_id || ') is not valid.');
    END IF;

    -- Validation: Check if the player is already part of the gameboard
    SELECT COUNT(*) INTO c FROM PCG_GAMEBOARD_PLAYER gp WHERE gp.GAMEBOARD_ID = P_Gameboard_ID AND gp.PLAYER_ID = v_upper_player_id;
    IF c = 0 THEN
        RAISE_APPLICATION_ERROR(-20004, 'Player (' || v_upper_player_id || ') is not a part of Gameboard ID (' || P_Gameboard_ID || ').');
    END IF;

    -- Validation: Check if the color is available to be used
    SELECT COUNT(*) INTO c FROM PCG_GAMEBOARD_COLOR gc WHERE gc.GAMEBOARD_ID = P_Gameboard_ID AND UPPER(gc.COLOR_NAME) = v_upper_color_name;
    IF c = 0 THEN
        RAISE_APPLICATION_ERROR(-20005, 'Color (' || v_upper_color_name || ') is not a part of the current gameboard.');
    END IF;

    -- Add the color to the appropriate user
    UPDATE PCG_GAMEBOARD_PLAYER gp
    SET gp.SELECTED_COLOR_NAME = (
        SELECT gc.COLOR_NAME
        FROM PCG_GAMEBOARD_COLOR gc
        WHERE gc.GAMEBOARD_ID = P_Gameboard_ID
        AND UPPER(gc.COLOR_NAME) = v_upper_color_name
    )
    WHERE gp.GAMEBOARD_ID = P_Gameboard_ID
    AND UPPER(gp.PLAYER_ID) = v_upper_player_id;
END;
