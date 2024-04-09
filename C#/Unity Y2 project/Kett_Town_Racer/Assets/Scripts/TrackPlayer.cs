using UnityEngine;

public class TrackPlayer : MonoBehaviour
{
    Transform playerTransform;
    float CamSpeed = 8;
    void Start()
    {
        playerTransform = GameObject.Find("Player").transform;
    }

    void Update()
    {
        float camX = Mathf.Lerp(transform.position.x, playerTransform.position.x, Time.deltaTime * CamSpeed);
        float camY = Mathf.Lerp(transform.position.y, playerTransform.position.y, Time.deltaTime * CamSpeed);
        float camZ = this.transform.position.z;
        this.transform.position = new Vector3(camX, camY, camZ);
    }
}
