class ScreenScript {
    static maxCharacterInNickForGameScreen = 25
    static maxCharacterInNickForLeaderboardScreen = 40

    static prepareText(text, maxCharacterInText) {
        let newText = `${text}`.trim()
        if (newText.length > maxCharacterInText)
            newText = newText.slice(0, maxCharacterInText).concat("...")
        return newText
    }

    static prepareScreen() {
        document.getElementById("current_level").textContent = `Уровень: ${gameCycle.currLevel}`
        document.getElementById("player_score").textContent = `Счёт: ${gameCycle.gameScoreProxy.score}`
        document.getElementById("player_name").textContent = ScreenScript.prepareText(
            "Игрок: " + localStorage["curr_player_name"],
            ScreenScript.maxCharacterInNickForGameScreen
        )
    }

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
        ScreenScript.prepareScreen()
        gameCycle.addKeyListener()
        UIEditor.drawTetrisField()
    }

    static toStartScreen() {
        gameCycle.removeKeyListener()
        let playerName = localStorage["curr_player_name"]
        saveRecordToLeaderboard(playerName)
        document.getElementById("game_screen").style.display = "none"
        document.getElementById("leaderboard_screen").style.display = "none"
        document.getElementById("start_screen").style.display = "block"
        UIEditor.clearTetrisField()
    }

    static toLeaderboardScreen() {
        let input = document.getElementById("name_input")
        if (input && input.value) {
            localStorage["curr_player_name"] = input.value
        } else {
            localStorage["curr_player_name"] = "Player 1"
        }

        document.getElementById("game_screen").style.display = "none"
        document.getElementById("start_screen").style.display = "none"
        document.getElementById("leaderboard_screen").style.display = "block"
        let leadearboardList = document.getElementById("leadearboard_list")
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
                    return -1
                else if (value1[0] < value2[0])
                    return 1
                else
                    return 0
            }
        })

        for (let i = 0; i < leaderboardArray.length; i++) {
            let nicknameField = document.createElement("div")
            nicknameField.className = "two-column-row-item-left"
            let scoreField = document.createElement("div")
            scoreField.className = "two-column-row-item-right"
            let listRow = document.createElement("div")
            listRow.className = "two-column-row"
            nicknameField.innerText = ScreenScript.prepareText(leaderboardArray[i][0], ScreenScript.maxCharacterInNickForLeaderboardScreen)
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
            leadearboardList.appendChild(listRow)
        }
    }
}





