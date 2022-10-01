class ScreenScript {
    static maxCharacterInNickForGameScreen = 25
    static maxCharacterInNickForLeaderboardScreen = 40

    // FIXME: поле с тетрисом не всегда очищается

    static toGameScreen() {
        let input = document.getElementById("name_input")
        if (input && input.value) {
            localStorage["curr_player_name"] = input.value
        } else {
            localStorage["curr_player_name"] = "Player 1"
        }
        document.getElementById("start_screen").style.display = "none"
        document.getElementById("leaderboard_screen").style.display = "none"
        document.getElementById("game_screen").style.display = "flex"
        gameCycle = new GameCycle()
        gameCycle.createField(UIEditor.fieldCanvas.clientWidth / UIEditor.squareSize, UIEditor.fieldCanvas.clientHeight / UIEditor.squareSize)
        ScreenScript.#prepareScreen()
        gameCycle.addKeyListener()
        UIEditor.drawTetrisField()
    }

    static toStartScreen() {
        if (gameCycle) {
            let playerName = localStorage["curr_player_name"]
            saveRecordToLeaderboard(playerName)
            gameCycle.removeKeyListener()
            UIEditor.clearTetrisField()
        }
        document.getElementById("game_screen").style.display = "none"
        document.getElementById("leaderboard_screen").style.display = "none"
        document.getElementById("start_screen").style.display = "flex"
    }

    static toLeaderboardScreen() {
        let input = document.getElementById("name_input")
        if (input && input.value) {
            localStorage["curr_player_name"] = input.value
        } else {
            localStorage["curr_player_name"] = "Player 1"
        }
        if (gameCycle) {
            gameCycle.removeKeyListener()
            UIEditor.clearTetrisField()
        }
        saveRecordToLeaderboard(localStorage["curr_player_name"] )
        document.getElementById("game_screen").style.display = "none"
        document.getElementById("start_screen").style.display = "none"
        document.getElementById("leaderboard_screen").style.display = "flex"
        let leaderboardList = document.getElementById("leadearboard_list")
        while (leaderboardList.children.length > 0) {
            leaderboardList.removeChild(leaderboardList.children[0])
        }
        let leaderboardStorage = parseMapFromJSON(localStorage["leaderboard"])
        let leaderboardArray = []
        leaderboardStorage.forEach((value, key) => {
            leaderboardArray.push([key, value])
        })
        leaderboardArray.sort((value1, value2) => {
            if (value1[1] > value2[1])
                return -1
            else if (value1[1] < value2[1])
                return 1
            else {
                if (value1[0] > value2[0])
                    return 1
                else if (value1[0] < value2[0])
                    return -1
                else
                    return 0
            }
        })
        ScreenScript.#addAllRowsToLeaderboard(leaderboardArray, leaderboardList);
    }

    static #prepareText(text, maxCharacterInText) {
        let newText = `${text}`.trim()
        if (newText.length > maxCharacterInText)
            newText = newText.slice(0, maxCharacterInText).concat("...")
        return newText
    }

    static #prepareScreen() {
        document.getElementById("current_level").textContent = `Уровень: ${gameCycle.currLevel}`
        document.getElementById("player_score").textContent = `Счёт: ${gameCycle.gameScoreProxy.score}`
        document.getElementById("player_name").textContent = ScreenScript.#prepareText(
            "Игрок: " + localStorage["curr_player_name"],
            ScreenScript.maxCharacterInNickForGameScreen
        )
    }

    static #addAllRowsToLeaderboard(leaderboardArray, leaderboardList) {
        for (let i = 0; i < leaderboardArray.length; i++) {
            let nicknameField = document.createElement("div")
            nicknameField.className = "two-column-row-item-left"
            let scoreField = document.createElement("div")
            scoreField.className = "two-column-row-item-right"
            let listRow = document.createElement("div")
            listRow.className = "two-column-row"
            nicknameField.innerText = ScreenScript.#prepareText(leaderboardArray[i][0], ScreenScript.maxCharacterInNickForLeaderboardScreen)
            scoreField.innerText = leaderboardArray[i][1]
            if (leaderboardArray[i][0] === localStorage["curr_player_name"]) {
                nicknameField.style.background = "#21e1ab"
                scoreField.style.background = "#21e1ab"
            } else {
                nicknameField.style.background = "#e1e4e6"
                scoreField.style.background = "#e1e4e6"
            }
            scoreField.style.textAlign = "center"
            listRow.appendChild(nicknameField)
            listRow.appendChild(scoreField)
            leaderboardList.appendChild(listRow)
        }
    }
}
