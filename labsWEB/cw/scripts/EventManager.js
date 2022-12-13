
export class EventManager {

    static keyToNum(key) {
        switch (key) {
            case "w": return 87;
            case "a": return 65;
            case "s": return 83;
            case "d": return 68;
            case "f": return 70;
            case  "e": return 101;
        }
    }

    constructor(heroAttack, heroTakeObject) {
        this.moveKeyBind = {
            87: { key: "w", pressed: false },
            65: { key: "a", pressed: false },
            83: { key: "s", pressed: false },
            68: { key: "d", pressed: false }
        }
        this.actionKeyBind = {
            70: { key: "f" },
            101: { key: "e" }
        }
        this.heroAttack = heroAttack
        this.takeObject = heroTakeObject
        document.body.addEventListener("keydown", this.onKeyDownFunc.bind(this))
        document.body.addEventListener("keyup", this.onKeyUpFunc.bind(this))
    }

    onKeyDownFunc(event) {
        let action = this.moveKeyBind[event.keyCode]
        if (action && action.key) {
            action.pressed = true
            return
        }
        action = this.actionKeyBind[event.keyCode]
        if (action && action.key) {
            switch (action.key) {
                case "f": this.heroAttack(); break;
                case "e": this.takeObject(); break;
            }
        }
    }
    onKeyUpFunc(event) {
        const action = this.moveKeyBind[event.keyCode].key
        if (action) {
            this.moveKeyBind[event.keyCode].pressed = false
        }
    }
}