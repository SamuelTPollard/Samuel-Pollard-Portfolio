using System.Collections.Generic;
using UnityEngine;

public class WeetabixCarrying : MonoBehaviour
{
    Rigidbody2D Player;
    [SerializeField]
    List<GameObject> boxes;
    List<GameObject> bears;
    GameObject HeldBox;
    GameHandler gameHandler;
    [SerializeField]
    bool isCarrying = false;
    void Start()
    {
        Player = gameObject.GetComponent<Rigidbody2D>();
        gameHandler = GameObject.Find("GameHandler").GetComponent<GameHandler>();
        boxes = new List<GameObject>(GameObject.FindGameObjectsWithTag("Weetabix"));
        bears = new List<GameObject>(GameObject.FindGameObjectsWithTag("Bear"));
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        if (collision.CompareTag("Weetabix") && Player.velocity.magnitude < 1)
        {
            isCarrying = true;
            HeldBox = collision.gameObject;
            foreach (GameObject b in boxes)
            {
                b.SetActive(false);
            }
            foreach (GameObject b in bears)
            {
                Debug.Log("Bear field on");
                b.transform.GetChild(0).gameObject.SetActive(true);
            }
        }
        if (collision.CompareTag("Bear") && (isCarrying == true) && (bears.Contains(collision.gameObject)) && Player.velocity.magnitude < 1)
        {
            collision.GetComponent<BearSatification>().Satisfy();
            DropWeetabix();
            bears.Remove(collision.gameObject);
            boxes.Remove(HeldBox);
            gameHandler.AddScore((int)gameHandler.remBTime);
            if (bears.Count == 0)
            {
                gameHandler.AddScore((int)gameHandler.remGTime * 100);
                Utilities.Loadscene("Menu");
            }
        }

    }

    public GameObject GetCurrentTarget()
    {
        if (isCarrying)
        {
            return Utilities.ClosestInList(gameObject.transform, bears); 
        }
        else if(bears.Count > 0) 
        {
            return Utilities.ClosestInList(gameObject.transform, boxes);
        }
        else
        {
            return gameObject;
        }
    }

    public void DropWeetabix()
    {
        isCarrying = false;
        foreach (GameObject b in boxes)
        {
            b.SetActive(true);
            b.transform.GetChild(0).gameObject.SetActive(true);
        }
        foreach (GameObject b in bears)
        {
            b.transform.GetChild(0).gameObject.SetActive(false);
        }
    }

    public bool GetCarrying()
    {
        return isCarrying;
    }

}

