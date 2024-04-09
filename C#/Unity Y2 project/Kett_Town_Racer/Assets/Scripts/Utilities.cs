using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Utilities : MonoBehaviour
{
    static public void Loadscene(string _scene)
    {
        SceneManager.LoadSceneAsync("Scenes/" + _scene);
    }

    static public void Quitgame()
    {
        Application.Quit();
    }

    static public GameObject ClosestInList(Transform self, List<GameObject> list)
    {
        float Dist = 9999999;
        GameObject ClosestObj = null;
        foreach (GameObject b in list)
        {
            if (Vector2.Distance(self.position, b.transform.position) < Dist)
            {
                Dist = Vector2.Distance(self.position, b.transform.position);
                ClosestObj = b;
            }
        }
        return ClosestObj;
    }

    static public Transform ClosestInList(Transform self, List<Transform> list)
    {
        float Dist = 9999999;
        Transform ClosestObj = null;
        foreach (Transform b in list)
        {
            if (Vector2.Distance(self.position, b.position) < Dist)
            {
                Dist = Vector2.Distance(self.position, b.position);
                ClosestObj = b;
            }
        }
        return ClosestObj;
    }
}

