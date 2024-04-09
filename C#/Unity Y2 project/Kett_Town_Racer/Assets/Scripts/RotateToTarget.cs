using UnityEngine;

public class RotateToTarget : MonoBehaviour
{
    Transform Player;
    [SerializeField]
    Transform Target;
    void Start()
    {
        Player = GameObject.Find("Player").transform;
    }

    void Update()
    {
        Target = Player.GetComponent<WeetabixCarrying>().GetCurrentTarget().transform;
        transform.up = Target.position - transform.position;
    }

}
