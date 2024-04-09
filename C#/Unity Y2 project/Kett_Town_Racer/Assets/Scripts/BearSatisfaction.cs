using UnityEngine;

public class BearSatification : MonoBehaviour
{
    SpriteRenderer spriteRenderer;
    public Sprite Satisfied;
    public bool IsSatified = false;
    void Start()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
    }
    public void Satisfy()
    {
        spriteRenderer.sprite = Satisfied;
        IsSatified = true;
    }

}
