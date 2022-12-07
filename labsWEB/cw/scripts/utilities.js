
function parseMapFromJSON (jsonObject) {
    let parseJson = JSON.parse(jsonObject)
    return new Map(Object.entries(parseJson))
}

function saveRecordToLeaderboard(playerName) {
    if (localStorage.getItem("leaderboard") == null) {
        let leaderboard = new Map() // создание новой таблицы лидеров
        if (true /*gameCycle && gameCycle.gameScoreProxy*/) { // FIXME
            leaderboard.set(playerName, 10 /*gameCycle.gameScoreProxy.score*/) // FIXME
        } else {
            leaderboard.set(playerName, 0)
        }
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard))
    } else {
        let leaderboard = parseMapFromJSON(localStorage["leaderboard"])
        let record = 0
        if (leaderboard.has(playerName))
            record = leaderboard.get(playerName)
        if (true/*gameCycle && gameCycle.gameScoreProxy*/) {  // FIXME
            leaderboard.set(playerName, Math.max(10/*gameCycle.gameScoreProxy.score*/, record))
        } else {
            leaderboard.set(playerName, record)
        }
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard)) // обновление рекорда
    }
}