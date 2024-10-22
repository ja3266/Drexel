CREATE OR REPLACE PROCEDURE PCG_JOIN_GAMEBOARD (
    P_Gameboard_ID IN NUMBER,
    P_Player_ID IN VARCHAR2
)
IS
    c INTEGER;
    v_max_players INTEGER;
    v_player_count INTEGER;
    v_upper_player_id VARCHAR2(50);  -- Local variable to hold the uppercase Player_ID
BEGIN
    -- Convert P_Player_ID to uppercase and store in the local variable
    v_upper_player_id := UPPER(P_Player_ID);

    -- Validation: Is the Gameboard ID valid?
    SELECT COUNT(*) INTO c FROM PCG_GAMEBOARD g WHERE g.GAMEBOARD_ID = P_Gameboard_ID;
    IF c = 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Gameboard ID (' || P_Gameboard_ID || ') is not valid.');
    END IF;

    -- Validation: Is the Player ID valid?
    SELECT COUNT(*) INTO c FROM PCG_PLAYER p WHERE p.PLAYER_ID = v_upper_player_id;
    IF c = 0 THEN
        RAISE_APPLICATION_ERROR(-20002, 'Player ID (' || v_upper_player_id || ') is not valid.');
    END IF;

    -- Validation: Check if the player is already part of the gameboard
    SELECT COUNT(*) INTO c 
    FROM PCG_GAMEBOARD_PLAYER gp 
    WHERE gp.GAMEBOARD_ID = P_Gameboard_ID AND gp.PLAYER_ID = v_upper_player_id;
    IF c > 0 THEN
        RAISE_APPLICATION_ERROR(-20003, 'Player (' || v_upper_player_id || ') is already part of Gameboard ID (' || P_Gameboard_ID || ').');
    END IF;

    -- Validation: Check if the player can join the gameboard (max number of players)
    SELECT NUMBER_OF_PLAYERS INTO v_max_players FROM PCG_GAMEBOARD WHERE GAMEBOARD_ID = P_Gameboard_ID;

    SELECT COUNT(*) INTO v_player_count FROM PCG_GAMEBOARD_PLAYER gp 
    WHERE gp.GAMEBOARD_ID = P_Gameboard_ID AND gp.ROLE = 'Player';

    IF v_player_count >= v_max_players THEN
        RAISE_APPLICATION_ERROR(-20004, 'Gameboard ID (' || P_Gameboard_ID || ') has reached the maximum number of players (' || v_max_players || ').');
    END IF;

    -- Insert new player into PCG_GAMEBOARD_PLAYER table using the uppercase Player_ID
    INSERT INTO PCG_GAMEBOARD_PLAYER (GAMEBOARD_ID, PLAYER_ID, ROLE, ROLE_INDEX, SELECTED_COLOR_NAME)
    SELECT P_Gameboard_ID, v_upper_player_id, 'Player', COALESCE(MAX(ROLE_INDEX), 0) + 1, NULL
    FROM PCG_GAMEBOARD_PLAYER
    WHERE GAMEBOARD_ID = P_Gameboard_ID;

END;
