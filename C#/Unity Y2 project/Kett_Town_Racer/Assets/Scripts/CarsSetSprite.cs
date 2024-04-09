using UnityEngine;

public class CarsSetSprite : MonoBehaviour
{
    public Sprite Car_Blue;
    public Sprite Car_Green;
    public Sprite Car_Red;
    public Sprite Car_Grey;
    public Sprite Car_White;
    SpriteRenderer spriteRenderer;
    void Start()
    {
        Sprite[] CarSprites = { Car_Blue, Car_Green, Car_Red, Car_Grey, Car_White };
        spriteRenderer = GetComponent<SpriteRenderer>();
        spriteRenderer.sprite = CarSprites[Random.Range(0, CarSprites.Length)];
    }

}
