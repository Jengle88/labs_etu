
export class EventManager {

    setup(hero, movementManager) {
        this.hero = hero
        this.movementManager = movementManager
        this.keyBind = {
            87: "w",
            65: "a",
            83: "s",
            68: "d",
            70: "f",
        }
        document.body.addEventListener("keydown", this.onKeyDownFunc.bind(this))
    }

    onKeyDownFunc(event) {
        const action = this.keyBind[event.keyCode]
        if (action) {
            switch (action) {
                case "w": this.movementManager.moveHero(this.hero, "w"); break;
                case "a": this.movementManager.moveHero(this.hero, "a"); break;
                case "s": this.movementManager.moveHero(this.hero, "s"); break;
                case "d": this.movementManager.moveHero(this.hero, "d"); break;
                case "f": /*attack*/; break;
            }
        }
    }
}