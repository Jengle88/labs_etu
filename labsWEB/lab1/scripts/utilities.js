
function parseMapFromJSON (jsonObject) {
    let parseJson = JSON.parse(jsonObject)
    return new Map(Object.entries(parseJson))
}

function saveRecordToLeaderboard(playerName) {
    if (localStorage.getItem("leaderboard") == null) {
        let leaderboard = new Map() // создание новой таблицы лидеров
        leaderboard.set(playerName, 100) // TODO заменить 100 на значение очков
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard))
    } else {
        let leaderboard = parseMapFromJSON(localStorage["leaderboard"])
        leaderboard.set(playerName, 300) // TODO заменить 300 на значение очков
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard)) // обновление рекорда
    }
}