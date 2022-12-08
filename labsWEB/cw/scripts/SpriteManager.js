export class SpriteManager {
    static spritesName = Object.freeze({
        mainHeroR: "main_hero_r",
        enemy1L: "enemy1_l",
        heal1: "heal1"
    })

    constructor() {
        this.sprites = {}
    }

    loadAllSprites() {
        // TODO Дописать повороты персонажей
        this.sprites[SpriteManager.spritesName.mainHeroR] = new Image();
        this.sprites[SpriteManager.spritesName.mainHeroR].src = "images/main_hero_r.png"
        this.sprites[SpriteManager.spritesName.enemy1L] = new Image();
        this.sprites[SpriteManager.spritesName.enemy1L].src = "images/enemy1_l.png"
        this.sprites[SpriteManager.spritesName.heal1] = new Image();
        this.sprites[SpriteManager.spritesName.heal1].src = "images/heal1.png"
    }

    getSprite(spriteName) {
        if (spriteName in SpriteManager.spritesName) {
            return this.sprites[name]
        } else {
            throw `Can't find ${name} sprite`
        }
    }
}
