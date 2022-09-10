let gameCycle = null

class GameCycle {
    static #keyListener = (event) => {
        const keyName = event.key
        switch (keyName) {
            case "ArrowUp":
                alert("Стрелка вверх")
                break
            case "ArrowDown":
                alert("Стрелка вниз")
                break
            case "ArrowLeft":
                alert("Стрелка влево")
                break
            case "ArrowRight":
                alert("Стрелка вправо")
                break
            case " ":
                alert("Пробел")
                break
        }
    }

    constructor() {
        this.gameField = null
    }

    addKeyListener() {
        document.addEventListener('keydown', GameCycle.#keyListener)
    }

    createField(width, height) {
        this.gameField = new Field(width, height)
    }

    removeKeyListener() {
        document.removeEventListener('keydown', GameCycle.#keyListener)
    }
}


