export class SpriteManager {
    static spritesName = Object.freeze({
        level1Background: "level1Background",
        level2Background: "level2Background",
        mainHeroR: "mainHeroR",
        mainHeroL: "mainHeroL",
        enemy1L: "enemy1L",
        enemy1R: "enemy1R",
        heal1: "heal1"
    })

    constructor() {
        this.sprites = {}
        this.loadAllSprites()
    }

    loadAllSprites() {
        this.sprites[SpriteManager.spritesName.level1Background] = new Image()
        this.sprites[SpriteManager.spritesName.level1Background].src = "/images/city_level1_ready2.png"
        this.sprites[SpriteManager.spritesName.level2Background] = new Image()
        this.sprites[SpriteManager.spritesName.level2Background].src = "/images/city_level2_ready2.png"
        this.sprites[SpriteManager.spritesName.mainHeroR] = new Image();
        this.sprites[SpriteManager.spritesName.mainHeroR].src = "/images/main_hero_r.png"
        this.sprites[SpriteManager.spritesName.mainHeroL] = new Image();
        this.sprites[SpriteManager.spritesName.mainHeroL].src = "/images/main_hero_l.png"
        this.sprites[SpriteManager.spritesName.enemy1L] = new Image();
        this.sprites[SpriteManager.spritesName.enemy1L].src = "/images/enemy1_l.png"
        this.sprites[SpriteManager.spritesName.enemy1R] = new Image();
        this.sprites[SpriteManager.spritesName.enemy1R].src = "/images/enemy1_r.png"
        this.sprites[SpriteManager.spritesName.heal1] = new Image();
        this.sprites[SpriteManager.spritesName.heal1].src = "/images/heal1.png"
    }


    getSprite(spriteName) {
        if (spriteName in SpriteManager.spritesName) {
            return this.sprites[spriteName]
        } else {
            throw `Can't find ${spriteName} sprite`
        }
    }
}
