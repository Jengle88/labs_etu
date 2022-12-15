
function parseMapFromJSON (jsonObject) {
    let parseJson = JSON.parse(jsonObject)
    return new Map(Object.entries(parseJson))
}

function saveRecordToLeaderboard(playerName, score) {
    if (localStorage.getItem("leaderboard") == null) {
        let leaderboard = new Map() // создание новой таблицы лидеров
            leaderboard.set(playerName, score)
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard))
    } else {
        let leaderboard = parseMapFromJSON(localStorage["leaderboard"])
        let record = 0
        if (leaderboard.has(playerName))
            record = leaderboard.get(playerName)
        leaderboard.set(playerName, Math.max(score, record))
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard)) // обновление рекорда
    }
}